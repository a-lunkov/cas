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
 *      ASXMLRPCRequestParser.hpp
 *
 * $CAS$
 */
#ifndef _AS_XML_RPC_REQUEST_PARSER_HPP__
#define _AS_XML_RPC_REQUEST_PARSER_HPP__ 1

// C++ Includes
#include "ASRequestParser.hpp"
#include "ASXMLRPCHandler.hpp"
#include "ASXMLParser.hpp"
#include <CDT.hpp>

#include "STLString.hpp"

namespace CAS // C++ Application Server
{
// FWD
class ASXMLParser;

/**
  @class MultipartParser ASMultipartParser.hpp <ASMultipartParser.hpp>
  @brief RFC1867 Multipart POST requeset parser
*/
class ASXMLRPCRequestParser:
  public ASRequestParser
{
public:
	/**
	  @brief Constructor
	  @param pIXMLParser - XML request data handler
	*/
	ASXMLRPCRequestParser(CTPP::CDT  & oArguments);

	/**
	  @brief Parse chunk of data
	  @param szString - start of buffer
	  @param szStringEnd - end of buffer
	*/
	void ParseChunk(CCHAR_P szString, CCHAR_P szStringEnd);

	/**
	  @brief Get parser state
	  @return 0 - if success, -1 - if any error occured, 1 - if parsing is finished
	*/
	INT_32 GetState() const;

	/**
	  @brief End of parsing process
	*/
	void ParseDone();

	/**
	  @brief Get error description
	*/
	STLW::string GetError() const;

	/**
	  @brief A destructor
	*/
	~ASXMLRPCRequestParser() throw();

private:
	/** XML-RPC handler         */
	mutable ASXMLRPCHandler  oHandler;
	/** XML psrser              */
	ASXMLParser              oXMLParser;
	/** Return code             */
	INT_32                   iRC;
};

#endif // _AS_XML_RPC_REQUEST_PARSER_HPP__
} // namespace CAS
// End.
