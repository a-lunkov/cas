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
 *      BSONView.hpp
 *
 * $CAS$
 */

#include "ASDebugHelper.hpp"
#include "ASLoadableObject.hpp"
#include "ASLoader.hpp"
#include "ASLogger.hpp"
#include "ASUtil.hpp"
#include "ASView.hpp"

#include <CTPP2OutputCollector.hpp>
#include <CTPP2Util.hpp>

#include <sys/time.h>

using namespace CAS;

namespace CAS_MOD
{

/**
  @class BSONView
  @brief Application server object
*/
class BSONView:
  public ASView
{
public:
	/**
	  @brief A virtual destructor
	*/
	~BSONView() throw();

	/**
	  @brief Constructor
	*/
	BSONView();

private:
	/**
	  @brief Get handler name
	*/
	CCHAR_P GetObjectName() const;

	/**
	  @brief Write HTTP response
	  @param oData - data model
	  @param oResponse - response object
	  @param pResponseWriter - response writer object
	  @param oGlobalPool - global pool of objects
	  @param oVhostPool - virtual host pool
	  @param oRequestPool - requeset data pool
	  @param pContextData - context data
	  @param oIMC - Inter-Module communication object
	  @param oLogger - application server logger
	  @return VIEW_OK - if success, VIEW_ERROR - if any error occured
	*/
	INT_32 WriteResponse(CTPP::CDT         & oData,
	                     ASResponse        & oResponse,
	                     ASResponseWriter  & pResponseWriter,
	                     ASPool            & oGlobalPool,
	                     ASPool            & oVhostPool,
	                     ASPool            & oRequestPool,
	                     CTPP::CDT         & oLocationConfig,
	                     ASObject          * pContextData,
	                     CTPP::CDT         & oIMC,
	                     ASLogger          & oLogger);
};

EXPORT_HANDLER(BSONView)

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Class BSONView
//

//
// A constructor
//
BSONView::BSONView()
{
	;;
}

//
// Get handler name
//
CCHAR_P BSONView::GetObjectName() const { return "BSONView"; }

//
// Write HTTP response
//
INT_32 BSONView::WriteResponse(CTPP::CDT         & oData,
                               ASResponse        & oResponse,
                               ASResponseWriter  & oResponseWriter,
                               ASPool            & oGlobalPool,
                               ASPool            & oVhostPool,
                               ASPool            & oRequestPool,
                               CTPP::CDT         & oLocationConfig,
                               ASObject          * pContextData,
                               CTPP::CDT         & oIMC,
                               ASLogger          & oLogger)
{
	DEBUG_HELPER(&oLogger, "BSONView::WriteResponse");

	INT_32 iRC  = VIEW_ERROR;
	try
	{
		DEBUG_HELPER_MESSAGE("Write response headers");
		// Write response headers
		oResponseWriter.WriteHeader(oResponse);

		DEBUG_HELPER_MESSAGE("Write response body");

		// Dump data
		std::string sData;
//		CTPP::CDT2BSON(oData, sData);

		// Write data to the output collector
		oResponseWriter.GetBodyOutputCollector() -> Collect(sData.data(), sData.size());

		iRC = VIEW_OK;
	}
	catch (std::exception & e)
	{
		STLW::string sError("Error in BSONView: ");
		sError += e.what();
		oLogger.WriteLog(AS_LOG_EMERG, sError.c_str());
	}
	catch (...)
	{
		oLogger.WriteLog(AS_LOG_EMERG, "Unknown fatal error in BSONView");
	}

return iRC;
}

//
// A destructor
//
BSONView::~BSONView() throw()
{
	;;
}

} // namespace CAS_MOD
// End.
