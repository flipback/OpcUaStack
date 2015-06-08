#include "OpcUaStackCore/Base/os.h"
#include "OpcUaServerApplicationDemo/DemoLibrary/DemoLibrary.h"
#include "OpcUaStackServer/ServiceSetApplication/ApplicationService.h"
#include <iostream>

namespace OpcUaServerApplicationDemo
{

	DemoLibrary::DemoLibrary(void)
	: ApplicationIf()
	, namespaceIndex_(0)
	, readCallback_(boost::bind(&DemoLibrary::readValue, this, _1))
	, writeCallback_(boost::bind(&DemoLibrary::writeValue, this))
	, valueMap_()
	{
		std::cout << "DemoLibrary::construct" << std::endl;
	}

	DemoLibrary::~DemoLibrary(void)
	{
		std::cout << "DemoLibrary::destruct" << std::endl;
	}

	bool
	DemoLibrary::startup(void)
	{
		std::cout << "DemoLibrary::startup" << std::endl;

		// read namespace info from server service
		if (!getNamespaceInfo()) {
			return false;
		}

		// create value map
		if (!createValueMap()) {
			return false;
		}

		ServiceTransactionRegisterForward::SPtr trx = ServiceTransactionRegisterForward::construct();
		RegisterForwardRequest::SPtr req = trx->request();
		RegisterForwardResponse::SPtr res = trx->response();

		req->forwardInfoSync()->setReadCallback(readCallback_);
		req->forwardInfoSync()->setWriteCallback(writeCallback_);
		req->nodesToRegister()->resize(valueMap_.size());

		uint32_t pos = 0;
		ValueMap::iterator it;
		for (it = valueMap_.begin(); it != valueMap_.end(); it++) {
			OpcUaNodeId::SPtr nodeId = OpcUaNodeId::construct();
			*nodeId = it->first;

			req->nodesToRegister()->set(pos, nodeId);
			pos++;
		}

		service().sendSync(trx);
		if (trx->responseHeader()->serviceResult() != Success) {
			std::cout << "response error" << std::endl;
			return false;
		}

		OpcUaStatusCode statusCode;
		res->statusCodeArray()->get(0, statusCode);
		if (statusCode != Success) {
			std::cout << "register value error" << std::endl;
			return false;
		}

		std::cout << "register forward ok..." << std::endl;

		return true;
	}

	bool
	DemoLibrary::shutdown(void)
	{
		std::cout << "DemoLibrary::shutdown" << std::endl;
		return true;
	}

	bool
	DemoLibrary::getNamespaceInfo(void)
	{
		ServiceTransactionNamespaceInfo::SPtr trx = ServiceTransactionNamespaceInfo::construct();
		NamespaceInfoRequest::SPtr req = trx->request();
		NamespaceInfoResponse::SPtr res = trx->response();

		service().sendSync(trx);
		if (trx->responseHeader()->serviceResult() != Success) {
			std::cout << "NamespaceInfoResponse error" << std::endl;
			return false;
		}

		NamespaceInfoResponse::Index2NamespaceMap::iterator it;
		for (
		    it = res->index2NamespaceMap().begin();
			it != res->index2NamespaceMap().end();
			it++
		)
		{
			std::cout << "Index=" << it->first << " Namespace=" << it->second << std::endl;
			if (it->second == "http://yourorganisation.org/Test-Server-Lib/") {
				namespaceIndex_ = it->first;
			}
 		}

		return true;
	}

	OpcUaDataValue::SPtr
	DemoLibrary::createDataValue(void)
	{
		OpcUaDataValue::SPtr dataValue;
		dataValue = OpcUaDataValue::construct();
		dataValue->statusCode(Success);
		dataValue->sourceTimestamp(OpcUaDateTime(boost::posix_time::microsec_clock::universal_time()));
		dataValue->serverTimestamp(OpcUaDateTime(boost::posix_time::microsec_clock::universal_time()));
		return dataValue;
	}

	bool
	DemoLibrary::createValueMap(void)
	{
		OpcUaNodeId nodeId;
		OpcUaDataValue::SPtr dataValue;

		// SByte
		nodeId.set(200, namespaceIndex_);
		OpcUaSByte sByte(12);
		dataValue = createDataValue();
		dataValue->variant()->variant(sByte);
		valueMap_.insert(std::make_pair(nodeId, dataValue));

		// SByteByteArray
		nodeId.set(201, namespaceIndex_);
		OpcUaSByteArray::SPtr sByteArray = OpcUaSByteArray::construct();
		sByteArray->resize(3);
		for (uint32_t pos=0; pos<3;pos++) sByteArray->set(pos, pos);
		dataValue = createDataValue();
		dataValue->variant()->variant(sByteArray);
		valueMap_.insert(std::make_pair(nodeId, dataValue));

		return true;
	}

#if 0

	  <UAVariable NodeId="ns=1;i=202" BrowseName="1:Byte" DataType="i=3">
	    <DisplayName>ByteValue</DisplayName>
	    <Description>Byte test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:Byte>12</uax:Byte>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=203" BrowseName="1:ByteArray" DataType="i=3" ValueRank="1" ArrayDimensions="3">
	    <DisplayName>ByteArrayValue</DisplayName>
	    <Description>Byte array test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:ListOfByte>
	        <uax:Byte>1</uax:Byte>
	        <uax:Byte>2</uax:Byte>
	        <uax:Byte>3</uax:Byte>
	      </uax:ListOfByte>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=204" BrowseName="1:Int16" DataType="i=4">
	    <DisplayName>Int16Value</DisplayName>
	    <Description>Int16 test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:Int16>123</uax:Int16>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=205" BrowseName="1:Int16Array" DataType="i=4" ValueRank="1" ArrayDimensions="3">
	    <DisplayName>Int16ArrayValue</DisplayName>
	    <Description>Int16 array test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:ListOfInt16>
	        <uax:Int16>1</uax:Int16>
	        <uax:Int16>2</uax:Int16>
	        <uax:Int16>3</uax:Int16>
	      </uax:ListOfInt16>
	    </Value>
	  </UAVariable>

	   <UAVariable NodeId="ns=1;i=206" BrowseName="1:UInt16" DataType="i=5">
	    <DisplayName>UInt16Value</DisplayName>
	    <Description>UInt16 test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:UInt16>123</uax:UInt16>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=207" BrowseName="1:UInt16Array" DataType="i=5" ValueRank="1" ArrayDimensions="3">
	    <DisplayName>UInt16ArrayValue</DisplayName>
	    <Description>UInt16 array test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:ListOfUInt16>
	        <uax:UInt16>1</uax:UInt16>
	        <uax:UInt16>2</uax:UInt16>
	        <uax:UInt16>3</uax:UInt16>
	      </uax:ListOfUInt16>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=208" BrowseName="1:Int32" DataType="i=6">
	    <DisplayName>Int32Value</DisplayName>
	    <Description>int32 test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:Int32>123</uax:Int32>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=209" BrowseName="1:Int32Array" DataType="i=6" ValueRank="1" ArrayDimensions="3">
	    <DisplayName>Int32ArrayValue</DisplayName>
	    <Description>int32 array test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:ListOfInt32>
	        <uax:Int32>1</uax:Int32>
	        <uax:Int32>2</uax:Int32>
	        <uax:Int32>3</uax:Int32>
	      </uax:ListOfInt32>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=210" BrowseName="1:UInt32" DataType="i=7">
	    <DisplayName>UInt32Value</DisplayName>
	    <Description>uint32 test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:UInt32>123</uax:UInt32>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=211" BrowseName="1:UInt32Array" DataType="i=7" ValueRank="1" ArrayDimensions="3">
	    <DisplayName>UInt32ArrayValue</DisplayName>
	    <Description>uint32 array test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:ListOfUInt32>
	        <uax:UInt32>1</uax:UInt32>
	        <uax:UInt32>2</uax:UInt32>
	        <uax:UInt32>3</uax:UInt32>
	      </uax:ListOfUInt32>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=212" BrowseName="1:Int64" DataType="i=8">
	    <DisplayName>Int64Value</DisplayName>
	    <Description>int64 test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:Int64>123</uax:Int64>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=213" BrowseName="1:Int64Array" DataType="i=8" ValueRank="1" ArrayDimensions="3">
	    <DisplayName>Int64ArrayValue</DisplayName>
	    <Description>int64 array test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:ListOfInt64>
	        <uax:Int64>1</uax:Int64>
	        <uax:Int64>2</uax:Int64>
	        <uax:Int64>3</uax:Int64>
	      </uax:ListOfInt64>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=214" BrowseName="1:UInt64" DataType="i=9">
	    <DisplayName>UInt64Value</DisplayName>
	    <Description>uint64 test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:UInt64>123</uax:UInt64>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=215" BrowseName="1:UInt64Array" DataType="i=9" ValueRank="1" ArrayDimensions="3">
	    <DisplayName>UInt64ArrayValue</DisplayName>
	    <Description>uint64 array test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:ListOfUInt64>
	        <uax:UInt64>1</uax:UInt64>
	        <uax:UInt64>2</uax:UInt64>
	        <uax:UInt64>3</uax:UInt64>
	      </uax:ListOfUInt64>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=216" BrowseName="1:Float" DataType="i=10">
	    <DisplayName>FloatValue</DisplayName>
	    <Description>Float test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:Float>123</uax:Float>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=217" BrowseName="1:FloatArray" DataType="i=10" ValueRank="1" ArrayDimensions="3">
	    <DisplayName>FloatArrayValue</DisplayName>
	    <Description>Float array test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:ListOfFloat>
	        <uax:Float>1</uax:Float>
	        <uax:Float>2</uax:Float>
	        <uax:Float>3</uax:Float>
	      </uax:ListOfFloat>
	    </Value>
	  </UAVariable>

	   <UAVariable NodeId="ns=1;i=218" BrowseName="1:Double" DataType="i=11">
	    <DisplayName>DoubleValue</DisplayName>
	    <Description>Double test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:Double>123</uax:Double>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=219" BrowseName="1:DoubleArray" DataType="i=11" ValueRank="1" ArrayDimensions="3">
	    <DisplayName>DoubleArrayValue</DisplayName>
	    <Description>Double array test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:ListOfDouble>
	        <uax:Double>1</uax:Double>
	        <uax:Double>2</uax:Double>
	        <uax:Double>3</uax:Double>
	      </uax:ListOfDouble>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=220" BrowseName="1:Boolean" DataType="i=1">
	    <DisplayName>BooleanValue</DisplayName>
	    <Description>Boolean test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:Boolean>true</uax:Boolean>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=221" BrowseName="1:BooleanArray" DataType="i=1" ValueRank="1" ArrayDimensions="3">
	    <DisplayName>BooleanArrayValue</DisplayName>
	    <Description>Boolean array test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:ListOfBoolean>
	        <uax:Boolean>true</uax:Boolean>
	        <uax:Boolean>false</uax:Boolean>
	        <uax:Boolean>true</uax:Boolean>
	      </uax:ListOfBoolean>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=222" BrowseName="1:String" DataType="i=12">
	    <DisplayName>StringValue</DisplayName>
	    <Description>String test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:String>string</uax:String>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=223" BrowseName="1:StringArray" DataType="i=12" ValueRank="1" ArrayDimensions="3">
	    <DisplayName>StringArrayValue</DisplayName>
	    <Description>String array test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:ListOfString>
	        <uax:String>string1</uax:String>
	        <uax:String>string2</uax:String>
	        <uax:String>string3</uax:String>
	      </uax:ListOfString>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=224" BrowseName="1:ByteString" DataType="i=15">
	    <DisplayName>ByteStringValue</DisplayName>
	    <Description>ByteString test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:ByteString>bytestring</uax:ByteString>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=225" BrowseName="1:ByteStringArray" DataType="i=15" ValueRank="1" ArrayDimensions="3">
	    <DisplayName>ByteStringArrayValue</DisplayName>
	    <Description>ByteString array test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:ListOfByteString>
	        <uax:ByteString>bytestring1</uax:ByteString>
	        <uax:ByteString>bytestring2</uax:ByteString>
	        <uax:ByteString>bytestring3</uax:ByteString>
	      </uax:ListOfByteString>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=226" BrowseName="1:LocalizedText" DataType="i=21">
	    <DisplayName>LocalizedTextValue</DisplayName>
	    <Description>LocalizedText test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:LocalizedText>
		    <Locale>de</Locale>
			<Text>LocalizedText</Text>
		  </uax:LocalizedText>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=227" BrowseName="1:LocalizedTextArray" DataType="i=21" ValueRank="1" ArrayDimensions="3">
	    <DisplayName>LocalizedTextArrayValue</DisplayName>
	    <Description>LocalizedText array test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:ListOfLocalizedText>
	        <uax:LocalizedText>
		      <uax:Locale>de</uax:Locale>
			  <uax:Text>LocalizedText1</uax:Text>
		    </uax:LocalizedText>
		    <uax:LocalizedText>
		      <uax:Locale>de</uax:Locale>
			  <uax:Text>LocalizedText2</uax:Text>
		    </uax:LocalizedText>
		    <uax:LocalizedText>
		      <uax:Locale>de</uax:Locale>
			  <uax:Text>LocalizedText3</uax:Text>
		    </uax:LocalizedText>
	      </uax:ListLocalizedText>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=228" BrowseName="1:DateTime" DataType="i=13">
	    <DisplayName>DateTimeValue</DisplayName>
	    <Description>DateTime test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:DateTime>2015-01-01T01:01:00Z</uax:DateTime>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=229" BrowseName="1:DateTimeArray" DataType="i=13" ValueRank="1" ArrayDimensions="3">
	    <DisplayName>DateTimeValueArray</DisplayName>
	    <Description>DateTime array test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:ListOfDateTime>
	        <uax:DateTime>2015-01-01T01:01:00Z</uax:DateTime>
	        <uax:DateTime>2015-01-01T01:02:00Z</uax:DateTime>
	        <uax:DateTime>2015-01-01T01:03:00Z</uax:DateTime>
	      </uax:ListOfDateTime>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=230" BrowseName="1:Guid" DataType="i=14">
	    <DisplayName>GuidValue</DisplayName>
	    <Description>Guid test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:Guid><uax:String>00000001-0001-0001-0001-000000000001</uax:String></uax:Guid>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=231" BrowseName="1:GuidArray" DataType="i=14" ValueRank="1" ArrayDimensions="3">
	    <DisplayName>GuidValueArray</DisplayName>
	    <Description>Guid array test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:ListOfGuid>
	        <uax:Guid><uax:String>00000001-0001-0001-0001-000000000001</uax:String></uax:Guid>
			<uax:Guid><uax:String>00000001-0001-0001-0001-000000000002</uax:String></uax:Guid>
			<uax:Guid><uax:String>00000001-0001-0001-0001-000000000003</uax:String></uax:Guid>
	      </uax:ListOfGuid>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=232" BrowseName="1:NodeId" DataType="i=17">
	    <DisplayName>NodeIdValue</DisplayName>
	    <Description>NodeId test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:NodeId><uax:Identifier>ns=1;s=String</uax:Identifier></uax:NodeId>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=233" BrowseName="1:NodeIdArray" DataType="i=17" ValueRank="1" ArrayDimensions="3">
	    <DisplayName>NodeIdValueArray</DisplayName>
	    <Description>NodeId array test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:ListOfNodeId>
	        <uax:NodeId><uax:Identifier>ns=1;s=String1</uax:Identifier></uax:NodeId>
			<uax:NodeId><uax:Identifier>ns=1;i=1234</uax:Identifier></uax:NodeId>
			<uax:NodeId><uax:Identifier>ns=1;s=00000001-0001-0001-0001-000000000001</uax:Identifier></uax:NodeId>
	      </uax:ListOfNodeId>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=234" BrowseName="1:QualifiedName" DataType="i=20">
	    <DisplayName>QualifiedNameValue</DisplayName>
	    <Description>QualifiedName test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
		  <uax:QualifiedName>
	        <uax:NamespaceIndex>0</uax:NamespaceIndex>
	        <uax:Name>QualifiedName</uax:Name>
	      </uax:QualifiedName>
	    </Value>
	  </UAVariable>

	  <UAVariable NodeId="ns=1;i=235" BrowseName="1:QualifiedNameArray" DataType="i=20" ValueRank="1" ArrayDimensions="3">
	    <DisplayName Locale="de">QualifiedNameValueArray</DisplayName>
	    <Description Locale="de">QualifiedName array test value</Description>
	    <References>
	      <Reference ReferenceType="HasTypeDefinition">i=2138</Reference>
	      <Reference ReferenceType="HasComponent" IsForward="false">ns=1;i=2</Reference>
	    </References>
		<Value>
	      <uax:ListOfQualifiedName>
		  <uax:QualifiedName>
	        <uax:NamespaceIndex>1</uax:NamespaceIndex>
	        <uax:Name>QualifiedName1</uax:Name>
	      </uax:QualifiedName>
		  <uax:QualifiedName>
	        <uax:NamespaceIndex>1</uax:NamespaceIndex>
	        <uax:Name>QualifiedName2</uax:Name>
	      </uax:QualifiedName>
		  <uax:QualifiedName>
	        <uax:NamespaceIndex>1</uax:NamespaceIndex>
	        <uax:Name>QualifiedName3</uax:Name>
	      </uax:QualifiedName>
	      </uax:ListOfQualifiedName>
	    </Value>
	  </UAVariable>


#endif

	void
	DemoLibrary::readValue(ApplicationReadContext& applicationReadContext)
	{
	    std::cout << "read value ..." << applicationReadContext.nodeId_ << std::endl;

	    ValueMap::iterator it;
	    it = valueMap_.find(applicationReadContext.nodeId_);
	    if (it == valueMap_.end()) {
	    	applicationReadContext.statusCode_ = BadInternalError;
	    	return;
	    }
	    applicationReadContext.statusCode_ = Success;
	    it->second->copyTo(applicationReadContext.dataValue_);
	}

	void
	DemoLibrary::writeValue(void)
	{
		std::cout << "write value ..." << std::endl;
	}

}

extern "C" DLLEXPORT void  init(ApplicationIf** applicationIf) {
    *applicationIf = new OpcUaServerApplicationDemo::DemoLibrary();
}

