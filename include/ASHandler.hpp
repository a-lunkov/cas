/*-
 * Copyright (c) 2005 - 2016 CAS Dev Team
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the CAS Dev. Team nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *      ASHandler.hpp
 *
 * $CAS$
 */
#ifndef _AS_HANDLER_HPP__
#define _AS_HANDLER_HPP__ 1

/**
  @file ASHandler.hpp
  @brief Application server handler
*/
#include "ASLogger.hpp"
#include "ASModule.hpp"
#include "ASPool.hpp"
#include "ASRequest.hpp"
#include "ASResponse.hpp"

#define HANDLER_OK         0             // Success
#define HANDLER_DONE       1             // No further processing need
#define HANDLER_ERROR     -1             // Error occured

namespace CAS // C++ Application Server
{
/**
  @class ASHandler ASHandler.hpp <ASHandler.hpp>
  @brief Application server handler
*/
class ASHandler:
  public ASModule
{
public:
	/**
	  @brief Initialize handler
	  @param oGlobalPool - global pool of objects
	  @param oVhostPool - virtual host pool
	  @param oLocationConfig - handler configuration
	  @param pContextData - context data
	  @param oLogger - application server logger
	  @return HANDLER_OK - if success, HANDLER_ERROR - if any error occured
	*/
	virtual INT_32 InitLocation(ASPool       & oGlobalPool,
	                            ASPool       & oVhostPool,
	                            CTPP::CDT    & oLocationConfig,
	                            ASObject   * & pContextData,
	                            ASLogger     & oLogger);

	/**
	  @brief Initialize handler
	  @param oData - data model
	  @param oRequest - request object
	  @param oResponse - response object
	  @param oGlobalPool - global pool of objects
	  @param oVhostPool - virtual host pool
	  @param oRequestPool - requeset data pool
	  @param oLocationConfig - location configuration
	  @param pContextData - context data
	  @param oIMC - Inter-Module communication object
	  @param oLogger - application server logger
	  @return HANDLER_OK - if success, HANDLER_ERROR - if any error occured, HANDLER_DONE - if no futher processing need
	*/
	virtual INT_32 Handler(CTPP::CDT   & oData,
	                       ASRequest   & oRequest,
	                       ASResponse  & oResponse,
	                       ASPool      & oGlobalPool,
	                       ASPool      & oVhostPool,
	                       ASPool      & oRequestPool,
	                       CTPP::CDT   & oLocationConfig,
	                       ASObject    * pContextData,
	                       CTPP::CDT   & oIMC,
	                       ASLogger    & oLogger) = 0;

	/**
	  @brief Shutdown location hook
	  @param oGlobalPool - global pool of objects
	  @param oVhostPool - virtual host pool
	  @param oLocationConfig - handler configuration
	  @param pContextData - context data
	  @param oLogger - application server logger
	  @return HANDLER_OK - if success, HANDLER_ERROR - if any error occured
	*/
	virtual INT_32 ShutdownLocation(ASPool       & oGlobalPool,
	                                ASPool       & oVhostPool,
	                                CTPP::CDT    & oLocationConfig,
	                                ASObject   * & pContextData,
	                                ASLogger     & oLogger);

	/**
	  @brief Post-execution fixup
	  @param oGlobalPool - global pool of objects
	  @param oVhostPool - virtual host pool
	  @param oRequestPool - requeset data pool
	  @param oLocationConfig - location configuration
	  @param pContextData - context data
	  @param oIMC - Inter-Module communication object
	  @param oLogger - application server logger
	  @return HANDLER_OK - if success, HANDLER_ERROR - if any error occured, HANDLER_DONE - if no futher processing need
	*/
	virtual INT_32 Fixup(ASPool     & oGlobalPool,
	                     ASPool     & oVhostPool,
	                     ASPool     & oRequestPool,
	                     CTPP::CDT  & oLocationConfig,
	                     ASObject   * pContextData,
	                     CTPP::CDT  & oIMC,
	                     ASLogger   & oLogger);

	/**
	  @brief A virtual destructor
	*/
	virtual ~ASHandler() throw();

private:
	/**
	  @brief Get object type
	  @return human-readable type of object
	*/
	CCHAR_P GetModuleType() const;
};

} // namespace CAS
#endif // _AS_HANDLER_HPP__
// End.
