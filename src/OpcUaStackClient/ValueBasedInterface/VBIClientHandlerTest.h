/*
   Copyright 2015 Kai Huebl (kai@huebl-sgh.de)

   Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
   Datei nur in Übereinstimmung mit der Lizenz erlaubt.
   Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

   Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
   erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
   GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

   Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
   im Rahmen der Lizenz finden Sie in der Lizenz.

   Autor: Kai Huebl (kai@huebl-sgh.de)
 */

#ifndef __OpcUaStackClient_VBIClientHandlerTest_h__
#define __OpcUaStackClient_VBIClientHandlerTest_h__

#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackClient/ValueBasedInterface/VBIClient.h"

using namespace OpcUaStackCore;
using namespace OpcUaStackClient;

namespace OpcUaStackClient
{

	class DLLEXPORT VBIClientHandlerTest
	{
	  public:
		VBIClientHandlerTest(void)
	    : clientHandle_(0)
	    , sessionState_(SS_Disconnect)
	    , sessionStateUpdate_()
	    {
	    }
		~VBIClientHandlerTest(void)
		{
		}

		uint32_t clientHandle_;

		SessionState sessionState_;
		Condition sessionStateUpdate_;
		void sessionStateUpdate(uint32_t clientHandle, SessionBase& session, SessionState sessionState) {
			clientHandle_ = clientHandle;
			sessionState_ = sessionState;
			sessionStateUpdate_.conditionValueDec();
		}

	};

}

#endif
