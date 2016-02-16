#include "unittest.h"
#include "boost/asio.hpp"
#include "OpcUaStackCore/ServiceSet/HistoryReadRequest.h"
#include "OpcUaStackCore/ServiceSet/HistoryReadResponse.h"
#include "OpcUaStackCore/SecureChannel/MessageHeader.h"
#include "OpcUaStackCore/SecureChannel/SequenceHeader.h"
#include "OpcUaStackCore/Base/Utility.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaIdentifier.h"

#include <streambuf>
#include <iostream>

using namespace OpcUaStackCore;

BOOST_AUTO_TEST_SUITE(HistoryRead_)

BOOST_AUTO_TEST_CASE(HistoryRead_Title)
{
	std::cout << "HistoryRead_t" << std::endl;
}

BOOST_AUTO_TEST_CASE(HistoryRead_Request)
{
	RequestHeader::SPtr requestHeader = RequestHeader::construct();
	std::string str;
	uint32_t pos;
	OpcUaNodeId typeId;
	OpcUaGuid::SPtr opcUaGuidSPtr;
	HistoryReadValueId::SPtr historyReadValueIdSPtr;
	HistoryReadRequest::SPtr historyReadRequestSPtr;
	MessageHeader::SPtr messageHeaderSPtr;
	SequenceHeader::SPtr sequenceHeaderSPtr;
	boost::posix_time::ptime ptime = boost::posix_time::from_iso_string("16010101T000000.000000000");
	
	// stream
	boost::asio::streambuf sb1;
	std::iostream ios1(&sb1);
	boost::asio::streambuf sb2;
	std::iostream ios2(&sb2);
	boost::asio::streambuf sb;
	std::iostream ios(&sb);

	// encode security header
	OpcUaInt32 secureChannelId;
	OpcUaInt32 secureTokenId;

	secureChannelId = 153451225;
	secureTokenId = 1;

	OpcUaNumber::opcUaBinaryEncode(ios1, secureChannelId);
	OpcUaNumber::opcUaBinaryEncode(ios1, secureTokenId);

	// encode sequence header
	sequenceHeaderSPtr = SequenceHeader::construct();
	sequenceHeaderSPtr->sequenceNumber(54);
	sequenceHeaderSPtr->requestId(4);
	sequenceHeaderSPtr->opcUaBinaryEncode(ios1);

	// encode TypeId
	typeId.nodeId(OpcUaId_HistoryReadRequest_Encoding_DefaultBinary);
	typeId.opcUaBinaryEncode(ios1);

	// build
	historyReadRequestSPtr = HistoryReadRequest::construct();

	// build RequestHeader
	opcUaGuidSPtr = constructSPtr<OpcUaGuid>();
	*opcUaGuidSPtr = "0D4455B2-8D2F-B74F-864F-0AF5945DD833";
	
	requestHeader->sessionAuthenticationToken().namespaceIndex(1);
	requestHeader->sessionAuthenticationToken().nodeId(opcUaGuidSPtr);
	requestHeader->time(ptime);
	requestHeader->requestHandle(0);
	requestHeader->returnDisagnostics(0);
	requestHeader->timeoutHint(300000);

	// build Parameter
	historyReadRequestSPtr->timestampsToReturn(TimestampsToReturn_Both);
	historyReadRequestSPtr->releaseContinuationPoints(true);

	// build HistoryReadValueId
	historyReadValueIdSPtr = HistoryReadValueId::construct();
	historyReadValueIdSPtr->nodeId((OpcUaInt16) 2, (OpcUaInt32) 9);
	historyReadValueIdSPtr->indexRange("2:3");
	historyReadValueIdSPtr->dataEncoding().namespaceIndex((OpcUaInt16) 0);
	historyReadValueIdSPtr->continuationPoint() = "ABC";

	historyReadRequestSPtr->nodesToRead()->set(historyReadValueIdSPtr);

	// encode
	requestHeader->opcUaBinaryEncode(ios1);
	historyReadRequestSPtr->opcUaBinaryEncode(ios1);

	// encode MessageHeader
	messageHeaderSPtr = MessageHeader::construct();
	messageHeaderSPtr->messageType(MessageType_Message);
	messageHeaderSPtr->messageSize(OpcUaStackCore::count(sb1)+8);
	messageHeaderSPtr->opcUaBinaryEncode(ios2);

	// stream
	ios << ios2.rdbuf() << ios1.rdbuf();
	OpcUaStackCore::dumpHex(ios);
	
	std::stringstream ss;
	ss << "4d 53 47 46 6e 00 00 00  d9 7a 25 09 01 00 00 00" 
	   << "36 00 00 00 04 00 00 00  01 00 98 02 04 01 00 0d"
	   << "44 55 b2 8d 2f b7 4f 86  4f 0a f5 94 5d d8 33 00"
	   << "00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 ff"
       << "ff ff ff e0 93 04 00 00  00 00 00 00 00 02 00 00"
       << "00 01 01 00 00 00 01 02  09 00 03 00 00 00 32 3a"
       << "33 00 00 ff ff ff ff 03  00 00 00 41 42 43";

	BOOST_REQUIRE(OpcUaStackCore::compare(ios, ss.str(), pos) == true);

	// decode MessageHeader
	messageHeaderSPtr = MessageHeader::construct();
	messageHeaderSPtr->opcUaBinaryDecode(ios);
	BOOST_REQUIRE(messageHeaderSPtr->messageType() == MessageType_Message);

	// decode security header
	OpcUaNumber::opcUaBinaryDecode(ios, secureChannelId);
	BOOST_REQUIRE(secureChannelId == 153451225);
	OpcUaNumber::opcUaBinaryDecode(ios, secureTokenId);
	BOOST_REQUIRE(secureTokenId == 1);

	// decode sequence header
	sequenceHeaderSPtr = SequenceHeader::construct();
	sequenceHeaderSPtr->opcUaBinaryDecode(ios);
	BOOST_REQUIRE(sequenceHeaderSPtr->sequenceNumber() == 54);
	BOOST_REQUIRE(sequenceHeaderSPtr->requestId() == 4);

	// decode message type id
	typeId.opcUaBinaryDecode(ios);
	BOOST_REQUIRE(typeId.namespaceIndex() == 0);
	BOOST_REQUIRE(typeId.nodeId<OpcUaUInt32>() == OpcUaId_HistoryReadRequest_Encoding_DefaultBinary);

	// decode ReadRequest
	historyReadRequestSPtr = HistoryReadRequest::construct();
	requestHeader->opcUaBinaryDecode(ios);
	historyReadRequestSPtr->opcUaBinaryDecode(ios);

	str = *requestHeader->sessionAuthenticationToken().nodeId<OpcUaGuid::SPtr>();
	BOOST_REQUIRE(requestHeader->sessionAuthenticationToken().namespaceIndex() == 1);
	BOOST_REQUIRE(str == "0D4455B2-8D2F-B74F-864F-0AF5945DD833");
	BOOST_REQUIRE(requestHeader->time().dateTime() == ptime);
	BOOST_REQUIRE(requestHeader->requestHandle() == 0);
	BOOST_REQUIRE(requestHeader->returnDisagnostics() == 0);
	BOOST_REQUIRE(requestHeader->timeoutHint() == 300000);
	
	BOOST_REQUIRE(historyReadRequestSPtr->timestampsToReturn() == TimestampsToReturn_Both);
	BOOST_REQUIRE(historyReadRequestSPtr->releaseContinuationPoints() == true);

	BOOST_REQUIRE(historyReadRequestSPtr->nodesToRead()->size() == 1);
	historyReadValueIdSPtr = HistoryReadValueId::construct();
	historyReadRequestSPtr->nodesToRead()->get(historyReadValueIdSPtr);
	BOOST_REQUIRE(historyReadValueIdSPtr->nodeId()->namespaceIndex() == 2);
	BOOST_REQUIRE(historyReadValueIdSPtr->nodeId()->nodeId<OpcUaUInt32>() == 9);
	BOOST_REQUIRE(historyReadValueIdSPtr->indexRange() == "2:3");
	BOOST_REQUIRE(historyReadValueIdSPtr->dataEncoding().namespaceIndex() == 0);
	str = historyReadValueIdSPtr->continuationPoint();
	BOOST_REQUIRE(str == "ABC");
}


BOOST_AUTO_TEST_CASE(HistoryRead_Response)
{
	ResponseHeader::SPtr responseHeader = constructSPtr<ResponseHeader>();
	uint32_t pos;
	std::string str;
	OpcUaNodeId typeId;
	OpcUaStatusCode statusCode;
	HistoryReadResult::SPtr historyReadResultSPtr;
	HistoryReadResponse::SPtr historyReadResponseSPtr;
	MessageHeader::SPtr messageHeaderSPtr;
	SequenceHeader::SPtr sequenceHeaderSPtr;
	boost::posix_time::ptime ptime;
	
	// test-time
	ptime = boost::posix_time::from_iso_string("16010101T000000.000000000");
	
	// stream
	boost::asio::streambuf sb1;
	std::iostream ios1(&sb1);
	boost::asio::streambuf sb2;
	std::iostream ios2(&sb2);
	boost::asio::streambuf sb;
	std::iostream ios(&sb);

	// encode security header
	OpcUaInt32 secureChannelId;
	OpcUaInt32 secureTokenId;

	secureChannelId = 153451225;
	secureTokenId = 1;

	OpcUaNumber::opcUaBinaryEncode(ios1, secureChannelId);
	OpcUaNumber::opcUaBinaryEncode(ios1, secureTokenId);

	// encode sequence header
	sequenceHeaderSPtr = SequenceHeader::construct();
	sequenceHeaderSPtr->sequenceNumber(54);
	sequenceHeaderSPtr->requestId(4);
	sequenceHeaderSPtr->opcUaBinaryEncode(ios1);

	// encode TypeId
	typeId.nodeId(OpcUaId_HistoryReadResponse_Encoding_DefaultBinary);
	typeId.opcUaBinaryEncode(ios1);

	// build 
	historyReadResponseSPtr = constructSPtr<HistoryReadResponse>();
	responseHeader->time(ptime);
	responseHeader->requestHandle(0);
	responseHeader->serviceResult(statusCode);
	
	// build HistoryReadResult
	historyReadResultSPtr = HistoryReadResult::construct();
	historyReadResultSPtr->statusCode((OpcUaStatusCode)Success);
	historyReadResultSPtr->continuationPoint() = "ABC";
	historyReadResponseSPtr->results()->set(historyReadResultSPtr);

	// encode 
	responseHeader->opcUaBinaryEncode(ios1);
	historyReadResponseSPtr->opcUaBinaryEncode(ios1);

	// encode MessageHeader
	messageHeaderSPtr = MessageHeader::construct();
	messageHeaderSPtr->messageType(MessageType_Message);
	messageHeaderSPtr->messageSize(OpcUaStackCore::count(sb1)+8);
	messageHeaderSPtr->opcUaBinaryEncode(ios2);

	// stream
	ios << ios2.rdbuf() << ios1.rdbuf();
	OpcUaStackCore::dumpHex(ios);

	std::stringstream ss;
	ss << "4d 53 47 46 4a 00 00 00  d9 7a 25 09 01 00 00 00"
	   << "36 00 00 00 04 00 00 00  01 00 9b 02 00 00 00 00"
	   << "00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00"
	   << "00 00 00 00 01 00 00 00  00 00 00 00 03 00 00 00"
	   << "41 42 43 00 00 00 00 00  00 00";

	BOOST_REQUIRE(OpcUaStackCore::compare(ios, ss.str(), pos) == true);

	// decode MessageHeader
	messageHeaderSPtr = MessageHeader::construct();
	messageHeaderSPtr->opcUaBinaryDecode(ios);
	BOOST_REQUIRE(messageHeaderSPtr->messageType() == MessageType_Message);

	// decode security header
	OpcUaNumber::opcUaBinaryDecode(ios, secureChannelId);
	BOOST_REQUIRE(secureChannelId == 153451225);
	OpcUaNumber::opcUaBinaryDecode(ios, secureTokenId);
	BOOST_REQUIRE(secureTokenId == 1);

	// decode sequence header
	sequenceHeaderSPtr = SequenceHeader::construct();
	sequenceHeaderSPtr->opcUaBinaryDecode(ios);
	BOOST_REQUIRE(sequenceHeaderSPtr->sequenceNumber() == 54);
	BOOST_REQUIRE(sequenceHeaderSPtr->requestId() == 4);

	// decode message type id
	typeId.opcUaBinaryDecode(ios);
	BOOST_REQUIRE(typeId.namespaceIndex() == 0);
	BOOST_REQUIRE(typeId.nodeId<OpcUaUInt32>() == OpcUaId_HistoryReadResponse_Encoding_DefaultBinary);

	// decode 
	historyReadResponseSPtr = constructSPtr<HistoryReadResponse>();
	responseHeader->opcUaBinaryDecode(ios);
	historyReadResponseSPtr->opcUaBinaryDecode(ios);

	BOOST_REQUIRE(responseHeader->time().dateTime() == ptime);
	BOOST_REQUIRE(responseHeader->requestHandle() == 0);
	BOOST_REQUIRE(responseHeader->serviceResult() == Success);

	BOOST_REQUIRE(historyReadResponseSPtr->results()->size() == 1);
	historyReadResultSPtr = HistoryReadResult::construct();
	historyReadResponseSPtr->results()->get(historyReadResultSPtr);
	BOOST_REQUIRE(historyReadResultSPtr->statusCode() == Success);
	str = historyReadResultSPtr->continuationPoint();
	BOOST_REQUIRE(str == "ABC");
}

BOOST_AUTO_TEST_SUITE_END()
