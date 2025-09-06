// ======================================================================
// \title  OsResources.hpp
// \author laboratory10
// \brief  hpp file for OsResources component implementation class
// ======================================================================

#ifndef FreeRTOS_OsResources_HPP
#define FreeRTOS_OsResources_HPP

#include "FreeRTOS/Svc/OsResources/OsResourcesComponentAc.hpp"

namespace FreeRTOS {

class OsResources final : public OsResourcesComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct OsResources object
    OsResources(const char* const compName  //!< The component name
    );

    //! Destroy OsResources object
    ~OsResources();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for user-defined typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for run
    //!
    void Run_handler(const FwIndexType portNum, /*!< The port number*/
                     U32 context                /*!< The call order*/
    );
};

}  // namespace FreeRTOS

#endif
