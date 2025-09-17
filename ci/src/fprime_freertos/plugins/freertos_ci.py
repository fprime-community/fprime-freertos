""" fprime_freertos.plugins.freertos_ci: FreeRTOS CI implementation

This module allows FreeRTOS to build as part of the fprime.ci package
"""
from abc import abstractmethod, ABC
import logging
from pathlib import Path
import serial

import fprime_gds.plugin.definitions
from fprime_ci.ci import Ci
from fprime_ci.plugin.definitions import plugin
from fprime_ci.utilities import IOLogger

LOGGER = logging.getLogger(__name__)


@plugin(Ci)
class FreeRTOSCi(Ci):
    """ FreeRTOS CI plugin """
    class Keys(Ci.Keys):
        """ Additional keys used during the execution of the FreeRTOS plugin

        These keys are used as constants when accessing context and used to validate context automatically. These keys
        are supplied in the initial supplied context. To fully understand these keys, see: CiPlugin.Keys for a better
        description of the usage and format.
        """
        FLASH_COMMAND = "flash-command"
        FLASH_COMMAND__ATTRS__ = (False, list)

    def __init__(self, port:str, unframed_output:str):
        """ Initialize basic components """
        self.port = port
        self.monitor_fsw_thread = None
        self.unframed_output = unframed_output
        self.file_handle = None

    def wait_for_boot(self, file_handle, prompt="*** Booting FreeRTOS OS build"):
        """ Wait for the FreeRTOS boot to complete
        
        Args:
            file_handle: file-like object to read FreeRTOS output from
            prompt: string to wait for in the output
        """
        IOLogger.communicate(
            [file_handle],
            [IOLogger(None, logging.DEBUG, logger_name=f"[FreeRTOSConsole]")],
            timeout=20.0,
            end=lambda line, index: prompt in line and line.endswith("\n"),
            close=False,
        )
    
    def monitor_fsw_run(self, file_handle):
        """ Monitor the FSW running on the target hardware """
        self.monitor_fsw_thread = IOLogger.async_communicate(
            [file_handle],
            [IOLogger(None, logging.DEBUG, logger_name=f"[FreeRTOSConsole]")],
        )

    def load(self, context: dict):
        """ Load the software to target hardware after power-on

        This function may be overridden by platform developers to perform software loading actions in preparation post
        power-on. This is the most convenient place to copy files via an active program like scp  This step runs
        directly after power-on.

        The default implementation does nothing.

        Note: platforms with long boot times should confirm a successful boot code before attempting load operations.

        TODO: list variables containing software set-up
        Args:
            context: build context aggregated across all build steps
        Returns:
            context optionally augmented with plugin-specific preload data
        """
        flash_command = context.get(self.Keys.FLASH_COMMAND, None)
        process, _, (_, _) = self.subprocess(
            flash_command
        )
        # Make sure that the console port is openable then open it
        self.wait_until(lambda: Path(self.port).exists(), timeout=1.0)
        return context


    def launch(self, context: dict):
        """ Launch the software on the target hardware

        This function must be overridden by platform developers to perform software launching actions. This might
        include running the executable via SSH, passing launch codes to a serial console, restarting the hardware, or
        nothing.

        There is no default implementation for this function, platforms with no explicit launching steps must supply
        a no-op function.

        Args:
            context: build context aggregated across all build steps
        """
        #TODO: wait for acknowledge
        try:
            self.file_handle = open(self.unframed_output, "rb")
            #TODO: Check if we want to wait for boot
            #self.wait_for_boot(self.file_handle)
            self.monitor_fsw_run(self.file_handle)
        except serial.SerialException as exception:
            raise Exception(f"Failed to read: {exception}")
        return context

    def cleanup(self, context: dict):
        """ Cleanup """
        try:
            if self.monitor_fsw_thread is not None:
                IOLogger.join_communicate(self.monitor_fsw_thread)
        finally:
            try:
                self.file_handle.close()
            except Exception as e:
                pass
        return context

    @classmethod
    def get_name(cls):
        """ Returns the name of the plugin """
        return "freertos-ci"

    @classmethod
    def get_arguments(cls):
        """ Returns the arguments of the plugin """
        return {
            ("--port",): {
                "type": str,
                "default": "/dev/ttyACM0",
                "help": "Serial port for unified console logs and GDS interface",
            },
            ("--unframed-output",): {
                "type": str,
                "required": True,
                "help": "Path to the unframed data output file",
            }
        }