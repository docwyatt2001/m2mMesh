#ifndef m2mMesh_h
#define m2mMesh_h
//Comment out the following line to remove some unnecessary functions for interrogating the mesh in user applications
#define m2mMeshIncludeDebugFeatures
#define m2mMeshIncludeMeshInfoFeatures
#define m2mMeshIncludeRTCFeatures
#include <Arduino.h>

//Different base libraries are needed for ESP8266/ESP8285 and ESP32
#if defined(ESP8266)
	//Include the ESP8266 WiFi and ESP-Now libraries
	//Also define some missing values for return values to match the ESP32 equivalents
	#define ESP_OK 0
	#define ESP_ERR_ESPNOW_NOT_INIT 248
	#define ESP_ERR_ESPNOW_ARG 249
	#define ESP_ERR_ESPNOW_INTERNAL 250
	#define ESP_ERR_ESPNOW_NO_MEM 251
	#define ESP_ERR_ESPNOW_NOT_FOUND 252
	#define ESP_ERR_ESPNOW_IF 253
	#define ESP_FAIL 255
	#include <ESP8266WiFi.h>
	#if defined (m2mMeshIncludeRTCFeatures)
		#include <time.h>
	#endif
	extern "C" {
	#include <espnow.h>
	#include "user_interface.h"
	}
#elif defined(ESP32)
	//Include the ESP32 WiFi and ESP-Now libraries
	#include <WiFi.h>
	#if defined (m2mMeshIncludeRTCFeatures)
		#include <time.h>
	#endif
	extern "C" {
	#include <esp_now.h>
	}
#endif

#if defined(ESP8266)
#define M2MMESHRECEIVEBUFFERSIZE 6
#define M2MMESHAPPLICATIONBUFFERSIZE 3
#elif defined(ESP32)
#define M2MMESHRECEIVEBUFFERSIZE 12
#define M2MMESHAPPLICATIONBUFFERSIZE 6
#endif

#if defined(ESP8266) || defined(ESP32)
#include <functional>
#define M2MMESH_CALLBACK std::function<void(meshEvent)> eventCallback
#endif

enum class meshEvent : uint8_t {joined, left, stable, changing, complete, synced, message};

//Error messages if debug enabled
#ifdef m2mMeshIncludeDebugFeatures
#ifdef ESP32
#include <esp_err.h>
#endif
const char m2mMesherrorReadBeyondEndOfPacket[] PROGMEM = "\r\nApplication tried to read beyond end of packet";
const char m2mMeshstartedwithcapacityfordnodes[] PROGMEM = "\r\nMesh started with capacity for %u nodes";
const char m2mMeshOGMECHOR02x02x02x02x02x02xO02x02x02x02x02x02xTTLdHOPdLEN[] PROGMEM = "\r\nOGM ECHO R:%02x:%02x:%02x:%02x:%02x:%02x O:%02x:%02x:%02x:%02x:%02x:%02x TTL:%u HOP:%u LEN:%u";
const char m2mMesh02x02x02x02x02x02xsequencenumberprotectionenabled[] PROGMEM = "\r\n%02x:%02x:%02x:%02x:%02x:%02x sequence number protection enabled";
const char m2mMeshsoriginator02x02x02x02x02x02xchangedintervalfromdtod[] PROGMEM = "\r\n%s originator %02x:%02x:%02x:%02x:%02x:%02x changed interval from %u to %u";
const char nm2mMeshWARNINGunknowntypedfrom02x02x02x02x02x02x[] PROGMEM = "\r\nWARNING: unknown type %u from %02x:%02x:%02x:%02x:%02x:%02x";
const char m2mMeshsFWDR02x02x02x02x02x02xO02x02x02x02x02x02xTTLd[] PROGMEM = "\r\n%s FWD R:%02x:%02x:%02x:%02x:%02x:%02x O:%02x:%02x:%02x:%02x:%02x:%02x TTL:%u";
const char m2mMeshsFWDR02x02x02x02x02x02xO02x02x02x02x02x02xTTLdfailed[] PROGMEM = "\r\n%s FWD R:%02x:%02x:%02x:%02x:%02x:%02x O:%02x:%02x:%02x:%02x:%02x:%02x TTL:%u failed";
const char m2mMesh02x02x02x02x02x02xsequencenumberprotectiondisabledpossiblereboot[] PROGMEM = "\r\n%02x:%02x:%02x:%02x:%02x:%02x sequence number protection disabled, possible reboot";
const char TTL02dFLG02xSEQ08xLENdNBRd[] PROGMEM = "TTL:%02d FLG:%02x SEQ:%08x LEN:%u NBR:%u";
const char m2mMeshSent[] PROGMEM = "\r\nSent ";
const char m2mMeshELPRCVR02x02x02x02x02x02xO02x02x02x02x02x02xTTLdNBRS02dLENd[] PROGMEM = "\r\nELP RCV R:%02x:%02x:%02x:%02x:%02x:%02x O:%02x:%02x:%02x:%02x:%02x:%02x TTL:%u NBRS:%02d LEN:%u";
const char m2mMeshELPRCVR02x02x02x02x02x02xO02x02x02x02x02x02xTTLdLENd[] PROGMEM = "\r\nELP RCV R:%02x:%02x:%02x:%02x:%02x:%02x O:%02x:%02x:%02x:%02x:%02x:%02x TTL:%u LEN:%u";
const char m2mMeshELPneighbour02x02x02x02x02x02xthisnode[] PROGMEM = "\r\nELP neighbour %02x:%02x:%02x:%02x:%02x:%02x - this node";
const char m2mMeshELPneighbour02x02x02x02x02x02xnewnode[] PROGMEM = "\r\nELP neighbour %02x:%02x:%02x:%02x:%02x:%02x - new node";
const char m2mMeshELPneighbour02x02x02x02x02x02x[] PROGMEM = "\r\nELP neighbour %02x:%02x:%02x:%02x:%02x:%02x";
const char m2mMeshELP[] PROGMEM =  "\r\nELP ";
const char m2mMeshOGMSNDTTL02dFLG02xSEQ08xLENd[] PROGMEM = "\r\nOGM SND TTL:%02d FLG:%02x SEQ:%08x LEN:%u";
const char m2mMeshOGMSNDfailedTTL02dFlags02xSeq08xLENd[] PROGMEM = "\r\nOGM SND failed TTL:%02d Flags:%02x Seq:%08x LEN:%u";
const char m2mMeshOGMRCVR02x02x02x02x02x02xO02x02x02x02x02x02xTTLdHOPdLENd[] PROGMEM = "\r\nOGM RCV R:%02x:%02x:%02x:%02x:%02x:%02x O:%02x:%02x:%02x:%02x:%02x:%02x TTL:%u HOP:%u LEN:%u";
const char m2mMeshOGMR02x02x02x02x02x02xselectedforO02x02x02x02x02x02xTQ04x[] PROGMEM = "\r\nOGM R:%02x%02x%02x%02x%02x%02x selected for O:%02x%02x%02x%02x%02x%02x TQ:%04x";
const char m2mMeshOGMR02x02x02x02x02x02xforO02x02x02x02x02x02xinferiorTQ04x[] PROGMEM = "\r\nOGM R:%02x%02x%02x%02x%02x%02x for O:%02x%02x%02x%02x%02x%02x inferior TQ:%04x";
const char m2mMeshOGMR02x02x02x02x02x02xforO02x02x02x02x02x02xupdateTQ04x[] PROGMEM = "\r\nOGM R:%02x%02x%02x%02x%02x%02x for O:%02x%02x%02x%02x%02x%02x update TQ:%04x";
const char m2mMeshOGMR02x02x02x02x02x02xforO02x02x02x02x02x02xTQ04x[] PROGMEM = "\r\nOGM R:%02x%02x%02x%02x%02x%02x for O:%02x%02x%02x%02x%02x%02x TQ:%04x";
const char m2mMeshOGMforwardingchain02x02x02x02x02x02x[] PROGMEM = "\r\nOGM forwarding chain %02x:%02x:%02x:%02x:%02x:%02x";
const char m2mMeshOGMhoppenaltyappliedTQnow02x[] PROGMEM = "\r\nOGM hop penalty applied, TQ now %02x";
const char m2mMeshOGM02x02x02x02x02x02xhasbecomereachable[] PROGMEM = "\r\nOGM %02x%02x%02x%02x%02x%02x has become reachable";
const char m2mMeshOGM02x02x02x02x02x02xhasbecomeunreachable[] PROGMEM = "\r\nOGM %02x%02x%02x%02x%02x%02x has become unreachable";
const char m2mMeshNHSSND[] PROGMEM = "\r\nNHS SND";
const char TTL02dFLG02xSEQ08xLENd[] PROGMEM = " TTL:%02d FLG:%02x SEQ:%08x LEN:%u";
const char ORGd[] PROGMEM = " ORG:%u";
const char m2mMeshsuccess[] PROGMEM = "- success";
const char m2mMeshfailed[] PROGMEM = "- failed";
const char m2mMeshfailed_code_[] PROGMEM = "- failed code ";
const char m2mMeshNHSR02x02x02x02x02x02xO02x02x02x02x02x02xTTLdLengthd[] PROGMEM = "\r\nNHS R:%02x:%02x:%02x:%02x:%02x:%02x O:%02x:%02x:%02x:%02x:%02x:%02x TTL:%u Length:%u";
const char m2mMeshNHSUptimedms[] PROGMEM = "\r\nNHS Uptime %ums";
const char m2mMeshNHSCurrentFreeHeapdd[] PROGMEM = "\r\nNHS Current Free Heap %u/%u";
const char m2mMeshNHSdroppedpacketsddRXddTX[] PROGMEM = "\r\nNHS dropped packets %u/%uRX %u/%uTX";
const char m2mMeshNHSActiveneighboursddMAC02x02x02x02x02x02x[] PROGMEM = "\r\nNHS Active neighbours %u/%u MAC:%02x:%02x:%02x:%02x:%02x:%02x";
const char m2mMeshdiffers[] PROGMEM = " - differs ";
const char m2mMeshNHSCurrentTXpowerf[] PROGMEM = "\r\nNHS Current TX power %f";
const char m2mMeshNHSSupplyvoltagefV[] PROGMEM = "\r\nNHS Supply voltage %fV";
const char m2mMeshNHSMeshtimedms[] PROGMEM = "\r\nNHS Mesh time %ums";
const char m2mMeshNHSRTCtimeds[] PROGMEM = "\r\nNHS RTC time %u \"%s\"";
const char m2mMeshNHSRTCtimezonesset[] PROGMEM = "\r\nNHS RTC timezone \"%s\" set";
const char m2mMeshNHSnodenamelendschangedfroms[] PROGMEM = "\r\nNHS node name len=%u '%s' changed from '%s'!";
const char m2mMeshNHSnodenamelendsadded[] PROGMEM = "\r\nNHS node name len=%u '%s' added";
const char m2mMeshNHSnodenamelendsunchanged[] PROGMEM = "\r\nNHS node name len=%u '%s' unchanged";
const char m2mMeshNHScontainsdoriginators[] PROGMEM = "\r\nNHS contains %u originators";
const char m2mMeshNHSoriginatordata02x02x02x02x02x02xTQ02x[] PROGMEM = "\r\nNHS originator data %02x:%02x:%02x:%02x:%02x:%02x TQ:%02x";
const char m2mMeshUSRR02x02x02x02x02x02xO02x02x02x02x02x02xTTLdLengthd[] PROGMEM = "\r\nUSR R:%02x:%02x:%02x:%02x:%02x:%02x O:%02x:%02x:%02x:%02x:%02x:%02x TTL:%u Length:%u";
const char m2mMeshUSRpacketcontainsdfields[] PROGMEM =		"\r\nUSR packet contains %u fields";
const char m2mMeshUSRdatafielddboolfalse[] PROGMEM =			"\r\nUSR data field %u bool false";
const char m2mMeshUSRdatafielddbooltrue[] PROGMEM =			"\r\nUSR data field %u bool true";
const char m2mMeshUSRdatafielddbooluarray[] PROGMEM =		"\r\nUSR data field %u bool[%u] array";
const char m2mMeshUSRdatadboolfalse[] PROGMEM =				"\r\nUSR data          bool[%u] = false";
const char m2mMeshUSRdatadbooltrue[] PROGMEM =				"\r\nUSR data          bool[%u] = true";
const char m2mMeshUSRdatafieldduint8_td[] PROGMEM =			"\r\nUSR data field %u uint8_t %u";
const char m2mMeshUSRdatafieldduint8_tuarray[] PROGMEM =	"\r\nUSR data field %u uint8_t[%u] array";
const char m2mMeshUSRdataduint8_td[] PROGMEM =				"\r\nUSR data          uint8_t[%u] = %u";
const char m2mMeshUSRdatafieldduint16_td[] PROGMEM =		"\r\nUSR data field %u uint16_t %u";
const char m2mMeshUSRdatafieldduint16_tuarray[] PROGMEM =	"\r\nUSR data field %u uint16_t[%u] array";
const char m2mMeshUSRdataduint16_td[] PROGMEM =				"\r\nUSR data          uint16_t[%u] = %u";
const char m2mMeshUSRdatafieldduint32_td[] PROGMEM =		"\r\nUSR data field %u uint32_t %u";
const char m2mMeshUSRdatafieldduint32_tuarray[] PROGMEM =	"\r\nUSR data field %u uint32_t[%u] array";
const char m2mMeshUSRdataduint32_td[] PROGMEM =				"\r\nUSR data          uint32_t[%u] = %u";
const char m2mMeshUSRdatafieldduint64_td[] PROGMEM =		"\r\nUSR data field %u uint64_t %u";
const char m2mMeshUSRdatafieldduint64_tuarray[] PROGMEM =	"\r\nUSR data field %u uint64_t[%u] array";
const char m2mMeshUSRdataduint64_td[] PROGMEM =				"\r\nUSR data          uint64_t[%u] = %u";
const char m2mMeshUSRdatafielddint8_td[] PROGMEM =			"\r\nUSR data field %u int8_t %d";
const char m2mMeshUSRdatafielddint8_tuarray[] PROGMEM =		"\r\nUSR data field %u int8_t[%u] array";
const char m2mMeshUSRdatadint8_td[] PROGMEM =				"\r\nUSR data          int8_t[%u] = %d";
const char m2mMeshUSRdatafielddint16_td[] PROGMEM =			"\r\nUSR data field %u int16_t %d";
const char m2mMeshUSRdatafielddint16_tuarray[] PROGMEM =	"\r\nUSR data field %u int16_t[%u] array";
const char m2mMeshUSRdatadint16_td[] PROGMEM =				"\r\nUSR data          int16_t[%u] = %d";
const char m2mMeshUSRdatafielddint32_td[] PROGMEM =			"\r\nUSR data field %u int32_t %d";
const char m2mMeshUSRdatafielddint32_tuarray[] PROGMEM =	"\r\nUSR data field %u int32_t[%u] array";
const char m2mMeshUSRdatadint32_td[] PROGMEM =				"\r\nUSR data          int32_t[%u] = %d";
const char m2mMeshUSRdatafielddint64_td[] PROGMEM =			"\r\nUSR data field %u int64_t %d";
const char m2mMeshUSRdatafielddint64_tuarray[] PROGMEM =	"\r\nUSR data field %u int64_t[%u] array";
const char m2mMeshUSRdatadint64_td[] PROGMEM =				"\r\nUSR data          int64_t[%u] = %d";
const char m2mMeshUSRdatafielddfloatf[] PROGMEM =			"\r\nUSR data field %u float %f";
const char m2mMeshUSRdatafielddfloatuarray[] PROGMEM =		"\r\nUSR data field %u float[%u] array";
const char m2mMeshUSRdatadfloatf[] PROGMEM =				"\r\nUSR data          float[%u] = %f";
const char m2mMeshUSRdatafieldddoublef[] PROGMEM =			"\r\nUSR data field %u double %f";
const char m2mMeshUSRdatafieldddoubleuarray[] PROGMEM =		"\r\nUSR data field %u double[%u] array";
const char m2mMeshUSRdataddoublef[] PROGMEM =				"\r\nUSR data          double[%u] = %f";
const char m2mMeshUSRdatafielddcharc[] PROGMEM =			"\r\nUSR data field %u char '%c'";
const char m2mMeshUSRdatafielddcharuarray[] PROGMEM =		"\r\nUSR data field %u char[%u] array";
const char m2mMeshUSRdatadcharc[] PROGMEM =					"\r\nUSR data          char[%u] = %c";
const char m2mMeshUSRdatafielddStringlends[] PROGMEM =		" \r\nUSR data field %u String len=%u \"%s\"";
const char m2mMeshUSRdatafielddcstringlends[] PROGMEM =	" \r\nUSR data field %u C string len=%u \"%s\"";
const char m2mMeshUSRdatafielddunknowntypedstoppingdecode[] PROGMEM = " \r\nUSR data field %u unknown type %02x, stopping decode ";
const char m2mMeshNHS02x02x02x02x02x02xisnowthetimeserver[] PROGMEM = "\r\nNHS %02x:%02x:%02x:%02x:%02x:%02x is now the time server";
const char m2mMeshNHStimeoffsetnegdms[] PROGMEM = "\r\nNHS time offset -%ums";
const char m2mMeshNHStimeoffsetposdms[] PROGMEM = "\r\nNHS time offset +%ums";
const char m2mMeshNHSmeshtimesettos[] PROGMEM = "\r\nNHS mesh time set to %s";
const char m2mMesh02x02x02x02x02x02xdbytesm2mMeshType[] PROGMEM = "%02x:%02x:%02x:%02x:%02x:%02x %u bytes\r\nType:";
const char m2mMeshChecksumx[] PROGMEM = " Checksum:%02x";
const char m2mMeshTTLd[] PROGMEM = " TTL:%u";
const char m2mMeshFlags2x[] PROGMEM = " Flags:%02x";
const char m2mMeshSequencenumberd[] PROGMEM = " Sequence number:%u\r\n";
const char m2mMeshSrc02x02x02x02x02x02x[] PROGMEM = "Src:%02x:%02x:%02x:%02x:%02x:%02x";
const char m2mMeshDst02x02x02x02x02x02x[] PROGMEM = " Dst:%02x:%02x:%02x:%02x:%02x:%02x";
const char m2mMeshData02x02x02x02x02x02x02x02x[] PROGMEM =	"\r\nData:%02x %02x %02x %02x %02x %02x %02x %02x";
const char m2mMeshData02x02x02x02x02x02x02x[] PROGMEM =		"\r\nData:%02x %02x %02x %02x %02x %02x %02x --";
const char m2mMeshData02x02x02x02x02x02x[] PROGMEM =		"\r\nData:%02x %02x %02x %02x %02x %02x --";
const char m2mMeshData02x02x02x02x02x[] PROGMEM =			"\r\nData:%02x %02x %02x %02x %02x --";
const char m2mMeshData02x02x02x02x[] PROGMEM =				"\r\nData:%02x %02x %02x %02x --";
const char m2mMeshData02x02x02x[] PROGMEM =					"\r\nData:%02x %02x %02x --";
const char m2mMeshData02x02x[] PROGMEM =					"\r\nData:%02x %02x --";
const char m2mMeshData02x[] PROGMEM =						"\r\nData:%02x --";
const char m2mMesh02x02x02x02x02x02xaddedidd[] PROGMEM = 		"%02x:%02x:%02x:%02x:%02x:%02x added id=%u";
const char m2mMesh02x02x02x02x02x02xcouldnotbeadded[] PROGMEM = "%02x:%02x:%02x:%02x:%02x:%02x could not be added";
const char m2mMeshNodenamesettos[] PROGMEM = "\r\nNode name set to '%s'";
const char m2mMeshSendingpackettype02xversion02x[] PROGMEM = "\r\nSending packet type %02x version %02x";
const char m2mMeshUSRSNDO02x02x02x02x02x02xTTL02dFlags02x[] PROGMEM = "\r\nUSR SND O:%02x%02x%02x%02x%02x%02x TTL:%02d Flags:%02x";
const char m2mMeshstartedwithautomaticallocationofmemoryStabilitymaybeimpacted[] PROGMEM = "\r\nstarted with automatic allocation of memory. Stability may be impacted.";
const char m2mMeshTTL02dFLG02xSEQ08xLENd[] PROGMEM = "TTL:%02d FLG:%02x SEQ:%08x LEN:%u";
const char m2mMeshTIMEs[] PROGMEM = " TIME:%s";
const char m2mMeshd02x[] PROGMEM = "%u/%02x ";
const char m2mMeshDstALL[] PROGMEM = " Dst:ALL";
const char m2mMeshIntervalu[] PROGMEM = " Interval:%u";
const char m2mMeshdebuggingenabled[] PROGMEM = "Mesh debugging enabled";
const char m2mMeshdebuggingdisabled[] PROGMEM = "Mesh debugging disabled";
const char m2mMeshinitialisingWiFi[] PROGMEM = "\r\nMesh initialising WiFi ";
const char m2mMeshinitialisingESPNOW[] PROGMEM = "\r\nMesh initialising ESP-NOW ";
const char m2mMeshWiFiStatus[] PROGMEM = "\r\nWiFi status:";
const char m2mMeshaddingbroadcastMACaddressasapeertoenablemeshdiscovery[] PROGMEM = "Adding broadcast MAC address as a 'peer' to enable mesh discovery ";
const char m2mMeshaddedpeerxxxxxxchannelu[] PROGMEM = "\r\nAdded ESP-Now peer %02x:%02x:%02x:%02x:%02x:%02x channel:%u %u/%u";
const char m2mMeshremovedpeerxxxxxx[] PROGMEM = "\r\nRemoved ESP-Now peer %02x:%02x:%02x:%02x:%02x:%02x %u/%u";
const char m2mMeshReceivedfrom[] PROGMEM = "Received from ";
const char m2mMeshRTR[] PROGMEM = "\r\nRTR ";
const char m2mMeshSoftAPison[] PROGMEM = " SoftAP is on";
const char m2mMeshlesspreferred[] PROGMEM = " less preferred";
const char m2mMeshNHSUnabletostorenodenamenotenoughmemory[] PROGMEM = "\r\nNHS Unable to store node name, not enough memory";
const char m2mMeshnew[] PROGMEM = " - new";
const char m2mMeshthisnode[] PROGMEM = " - this node";
const char m2mMeshPreviousUSRmessagenotreadpacketdropped[] PROGMEM = "\r\nPrevious USR message not read, packet dropped";
const char m2mMeshTimeserverhasgoneofflinetakingovertimeserverrole[] PROGMEM = "Time server has gone offline, taking over time server role";
const char m2mMeshfillRCVbufferslotd[] PROGMEM = 	"\r\nFill RCV buffer slot %u %u bytes %s from %02x:%02x:%02x:%02x:%02x:%02x";
const char m2mMeshreadRCVbufferslotd[] PROGMEM =	"\r\nRead RCV buffer slot %u %u bytes %s from %02x:%02x:%02x:%02x:%02x:%02x";
const char m2mMeshreadRCVbufferfull[] PROGMEM =	"\r\nRead RCV buffer full";
const char m2mMeshfillAPPbufferslotd[] PROGMEM = 	"\r\nFill APP buffer slot %u %u bytes %s from %02x:%02x:%02x:%02x:%02x:%02x";
const char m2mMeshreadAPPbufferslotd[] PROGMEM =	"\r\nRead APP buffer slot %u %u bytes %s from %02x:%02x:%02x:%02x:%02x:%02x";
const char m2mMeshreadAPPbufferfull[] PROGMEM =	"\r\nRead APP buffer full";
const char m2mMeshchecksumValid[] PROGMEM =	"\r\nChecksum valid";
const char m2mMeshchecksumInvalidreceived2xshouldbe2x[] PROGMEM =	"\r\nChecksum invalid, received %02x, should be %02x";
//const char m2mMeshPacketsentto02x02x02x02x02x02x[] PROGMEM = "Packet sent to %02x:%02x:%02x:%02x:%02x:%02x";
//const char m2mMeshNHSincluded02x02x02x02x02x02xTQ02x[] PROGMEM = "\r\nNHS included %02x:%02x:%02x:%02x:%02x:%02x TQ:%02x";
//const char m2mMeshNHSincludeddoriginators[] PROGMEM = "\r\nNHS included %u originators";
#endif

//Unions used to pack data into packets

union unsignedIntToBytes
{
  uint8_t b[2];
  uint16_t value;
};

union unsignedLongToBytes
{
  uint8_t b[4];
  uint32_t value;
};

union unsignedLongLongToBytes
{
  uint8_t b[8];
  uint64_t value;
};

union intToBytes
{
  uint8_t b[2];
  int16_t value;
};

union longToBytes
{
  uint8_t b[4];
  int32_t value;
};

union longLongToBytes
{
  uint8_t b[8];
  int64_t value;
};

union floatToBytes
{
  uint8_t b[4];
  float value;
};

union doubleToBytes
{
  uint8_t b[8];
  double value;
};

struct m2mMeshOriginatorInfo							//A structure for storing information about originators (nodes)
{
	char *nodeName = nullptr;							//Node name, which may or may not be set. Memory is allocated dynamically at runtime
	uint8_t macAddress[6] = {0, 0, 0, 0, 0, 0};			//Defaults to nothing
	uint8_t channel = 0;								//Defaults to whatever the mesh channel is
	uint8_t flags = 0;									//Defaults to no flags
	//ESP-Now peer management
	bool isCurrentlyPeer = false;						//Is it an ESP-Now peer
	uint32_t peerNeeded = 0;							//Last time the peer was needed
	//Mesh info
	uint8_t numberOfOriginators = 0;					//Number of originators this node asserts is in the mesh
	uint8_t numberOfActiveNeighbours = 0;				//Number of active neighbours this node sees traffic from
	//Routing info
	uint32_t lastSequenceNumber = 0;					//The last sequence number from this originator
	bool sequenceNumberProtectionWindowActive = true;	//Used to handle rollover and out of sequence packets
	uint32_t lastSeen[5] = {0, 0, 0, 0, 0};				//The last time each protocol ELP/OGM/NHS/USR/FSP was seen
	uint32_t interval[5] = {0, 0, 0, 0, 0};				//The expected interval for each protocol ELP/OGM/NHS/USR/FSP
	uint16_t ogmReceived = 0;							//The number of OGMs received
	uint32_t ogmReceiptLastConfirmed = 0;				//Last time an incoming OGM was checked for
	uint16_t ogmEchoes = 0;								//The number of OGM ecoes received
	uint32_t ogmEchoLastConfirmed = 0;					//Time of the last OGM echo
	uint16_t ltq = 0;									//Local Transmission Quality
	uint16_t gtq = 0;									//Global Transmission Quality
	uint8_t selectedRouter = 255;						//Best global router for this node, which starts as unknown
	//Health info
	uint32_t uptime = 0;								//The time the device has been up
	float supplyVoltage = 0;							//Supply voltage as measured by the ESP, whether it is the Vcc or battery voltage up to you
	float currentTxPower = 0;							//Radio transmission power, if managing transmit power
	uint32_t currentFreeHeap = 0;						//Current free heap
	uint32_t initialFreeHeap = 0;						//Initial free heap
	uint32_t largestFreeBlock = 0;						//Largest free block
	uint8_t heapFragmentation = 0;						//Heap fragmentation
	uint32_t rxPackets = 0;								//Monitor buffer receive problems
	uint32_t txPackets = 0;								//Monitor buffer send problems
	uint32_t droppedRxPackets = 0;						//Monitor buffer receive problems
	uint32_t droppedTxPackets = 0;						//Monitor buffer send problems
};

struct m2mMeshPacketBuffer								//A structure for storing ESP-Now packets
{
	uint8_t macAddress[6] = {0, 0, 0, 0, 0, 0};			//Source or destination MAC address
	uint8_t length;										//Amount of data in the packet
	uint8_t data[250];									//Size the data for the largest possible packet
	uint32_t timestamp = 0;								//Time when the packet went into the buffer
};

class m2mMeshClass
{

	public:

		//Constructor functions
		m2mMeshClass();
		//Destructor function
		~m2mMeshClass();

		//Setup functions
		bool begin();										//Start the mesh, with the default maximum number of nodes (16)
		bool begin(uint8_t);								//Start the mesh with a specific maximum number of nodes. Set to 0 for unlimited dynamic allocation of memory, which may cause instability.
		bool begin(uint8_t, uint8_t);						//Start the mesh with a specific maximum number of nodes and channel.
		void end();											//Stop the mesh and free most memory. Configured items such as the node name or maximum number of nodes ARE retained but no originator/routing information.
		
		//Maintenance functions
		void housekeeping();								//Must be run at least once a second to make sure mesh packets are processed

		//Configuration functions
		bool nodeNameIsSet();								//Returns true if the node name is set, false otherwise
		bool nodeNameIsSet(uint8_t);						//Returns true if the node name is set for a specific node, false otherwise
		bool setNodeName(const char *);						//Set the node name
		bool setNodeName(char *);							//Set the node name
		bool setNodeName(String);							//Set the node name
		char * getNodeName();								//Get a pointer to the node name
		char * getNodeName(uint8_t);						//Get a pointer to the node name for another node
		uint8_t * getMeshAddress();							//Get a pointer to the mesh MAC address
		uint8_t * getMeshAddress(uint8_t);					//Get a pointer to the mesh MAC address	 for a specific node
		
		//RTC functions
		#if defined (m2mMeshIncludeRTCFeatures)
		void setNtpServer(const char *);					//Set an NTP server
		void setTimeZone(const char *);						//Set a timezone for the NTP server (only needed on one node)
		bool rtcConfigured();
		bool rtcSynced();
		bool actingAsRTCServer();							//Is THIS node acting as an RTC server
		bool actingAsRTCServer(const uint8_t);				//Is a particular node acting as an RTC server
		uint8_t rtcServer();								//ID of RTC server
		bool rtcValid();									//Is the RTC configured and valid? Works for client and server
		#endif
		
		//Status functions
		bool joined();										//Has this node joined the mesh
		bool stable();										//Has the mesh membership changed recently
		float supplyVoltage();								//Returns the supply voltage once the resistor ladder value is set
		bool synced();										//Returns true if 'mesh time' is synced
		bool amSyncServer();								//Returns true if this node is the 'mesh time' server
		uint8_t syncServer();								//Returns ID of the 'mesh time' server
		uint32_t syncedMillis();							//Returns 'mesh time' which should be broadly synced across all the nodes, useful for syncing events
		uint8_t numberOfNodes();							//Returns the total number of originators in the mesh
		uint8_t numberOfReachableNodes();				//Returns the number of originators reachable from this node
		uint32_t expectedUptime(uint8_t);					//Uptime of a node, assuming it has continued running

		//Sending data
		bool destination(uint8_t);			//Add a destination ID to a message. Without a destination it is flooded to the whole mesh.
		//bool destination(char *);			//Add a destination to a message. This can be a node name or MAC address, the function will attempt to distinguish between them.
		//bool destination(String);			//Add a destination to a message. This can be a node name or MAC address.
		bool destination(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);	//Add a destination MAC address
		uint8_t payloadLeft();				//Returns the number of bytes left in the packet, helps with checking before adding
		/*
		bool add(bool);						//Add a bool to a message
		bool add(uint8_t);					//Add an uint8_t to a message
		bool add(uint8_t *, uint8_t);		//Add an array of uint8_t, mostly used to send chunks of binary data
		bool add(uint16_t);					//Add an uint16_t to a message
		bool add(uint16_t*, uint8_t);		//Add an array of uint16_t to a message
		bool add(uint32_t);					//Add an uint32_t to a message
		bool add(uint64_t);					//Add an uint64_t to a message
		bool add(int8_t);					//Add an int8_t to a message
		bool add(int16_t);					//Add an int16_t to a message
		bool add(int32_t);					//Add an int32_t to a message
		bool add(int64_t);					//Add an int64_t to a message
		bool add(char);						//Add a char to a message
		bool add(float);					//Add a float to a message
		*/
		bool add(String);					//Add a String to a message, which is a special case
		bool add(const char *);				//Add a C string to a message, which is a special case
		bool add(char *);					//Add a C string to a message, which is a special case
		bool send(bool wait = true);		//Send the message now, optional 'wait' parameter defaults to true
		bool clearMessage();				//Clear the message without sending

		//Receiving data
		m2mMeshClass& setCallback(M2MMESH_CALLBACK);	//Set a callback for mesh events
		bool messageWaiting();				//Is there a message waiting
		uint8_t messageSize();				//Size of the message, perhaps not useful
		void markMessageRead();				//Marks the message as read, discarding any data left
		uint8_t sourceId();					//Which ID is the message from
		bool sourceMacAddress(uint8_t *);	//Which MAC address is the message from
		uint8_t dataAvailable();			//Is there data to read
		uint8_t nextDataType();				//Which type the next piece of data is
		
		//bool retrieve(uint8_t&);				//Retrieve uint8_t data from a message
		//bool retrieve(uint32_t&);				//Retrieve uint32_t data from a message
		//bool retrieve(uint64_t&);				//Retrieve uint64_t data from a message

		bool retrieveBool();					//Retrieve bool data from a message
		uint8_t retrieveUint8_t();				//Retrieve uint8_t data from a message
		uint16_t retrieveUint16_t();			//Retrieve uint16_t data from a message
		uint32_t retrieveUint32_t();			//Retrieve uint32_t data from a message
		uint64_t retrieveUint64_t();			//Retrieve uint64_t data from a message
		int8_t retrieveInt8_t();				//Retrieve int8_t data from a message
		int16_t retrieveInt16_t();				//Retrieve int16_t data from a message
		int32_t retrieveInt32_t();				//Retrieve int32_t data from a message
		int64_t retrieveInt64_t();				//Retrieve int64_t data from a message
		float retrieveFloat();					//Retrieve float data from a message
		double retrieveDouble();				//Retrieve double precision float data from a message
		char retrieveChar();					//Retrieve char data from a message
		uint8_t retrieveDataLength();			//Retrieve length of an array from a message
		bool retrieveStr(char *);				//Retrieve C string from a message NB will be null terminated automatically
		String retrieveString();				//Retrieve Arduino String data from a message
		//void retrieveUint8_tArray(uint8_t *);	//Retrieve int8_t array from a message
		//void retrieveUint16_tArray(uint16_t *);	//Retrieve int16_t array from a message
		void skipRetrieve();					//Skip retrieving this field

		//Generic templated retrieve function (which must be in the class definition)
		template<typename typeToRetrieve>
		void ICACHE_FLASH_ATTR retrieveArray(typeToRetrieve *data)
		{
			if(dataAvailable() == 0)
			{
				#ifdef m2mMeshIncludeDebugFeatures
				if(_debugEnabled == true && _loggingLevel & MESH_UI_LOG_WARNINGS)
				{
					_debugStream->print(m2mMesherrorReadBeyondEndOfPacket);
				}
				#endif
				//Return a dummy value if nothing available
			}
			else
			{
				_receivedUserPacketFieldCounter--;
				uint8_t dataLength = _numberOfPackedItems(_applicationBuffer[_applicationBufferReadIndex].data[_receivedUserPacketIndex],_applicationBuffer[_applicationBufferReadIndex].data[_receivedUserPacketIndex+1]) * sizeof(typeToRetrieve);
				_receivedUserPacketIndex+=_packingOverhead(_applicationBuffer[_applicationBufferReadIndex].data[_receivedUserPacketIndex]);
				memcpy(data,&_applicationBuffer[_applicationBufferReadIndex].data[_receivedUserPacketIndex],dataLength);
				_receivedUserPacketIndex+=dataLength;
				if(dataAvailable() == 0)
				{
					markMessageRead();
				}
			}
		}
		//Generic templated add functions (which must be in the class definition)
		template<typename typeToAdd>
		bool ICACHE_FLASH_ATTR add(typeToAdd dataToAdd)
		{
			_buildUserPacketHeader();
			uint8_t dataType = determineType(dataToAdd);
			if(dataType == USR_DATA_BOOL)	//Bool is a special case for packing
			{
				if(_userPacketBuffer.length + sizeof(dataToAdd) < USR_MAX_PACKET_SIZE)
				{
					if(dataToAdd == true)
					{
						_userPacketBuffer.data[_userPacketBuffer.length++] = USR_DATA_BOOL_TRUE;	//True
					}
					else
					{
						_userPacketBuffer.data[_userPacketBuffer.length++] = USR_DATA_BOOL;	//False
					}
					_userPacketBuffer.data[_userPacketFieldCounterIndex] = _userPacketBuffer.data[_userPacketFieldCounterIndex] + 1;	//Increment the field counter
					return(true);
				}
				else
				{
					return(false);	//Not enough space left in the packet
				}
			}
			else
			{
				if(_userPacketBuffer.length + sizeof(dataToAdd) + 1 < USR_MAX_PACKET_SIZE)
				{
					_userPacketBuffer.data[_userPacketBuffer.length++] = dataType;
					memcpy(&_userPacketBuffer.data[_userPacketBuffer.length],&dataToAdd,sizeof(dataToAdd));						//Copy in the data
					_userPacketBuffer.length+=sizeof(dataToAdd);														//Advance the index past the data
					_userPacketBuffer.data[_userPacketFieldCounterIndex] = _userPacketBuffer.data[_userPacketFieldCounterIndex] + 1;	//Increment the field counter
					return(true);
				}
				else
				{
					return(false);	//Not enough space left in the packet
				}
			}
		}
		template<typename typeToAdd>
		bool ICACHE_FLASH_ATTR add(typeToAdd* dataToAdd, uint8_t numberOfElements)
		{
			_buildUserPacketHeader();
			if(numberOfElements < 15)
			{
				if(_userPacketBuffer.length + sizeof(dataToAdd[0]) * numberOfElements < USR_MAX_PACKET_SIZE)
				{
					_userPacketBuffer.data[_userPacketBuffer.length++] = determinePointerType(dataToAdd) | (numberOfElements<<4);	//Mark that this field has 15 members or fewer
				}
				else
				{
					return(false);	//Not enough space left in the packet
				}
			}
			else
			{
				if(_userPacketBuffer.length + sizeof(dataToAdd[0]) * numberOfElements + 1 < USR_MAX_PACKET_SIZE)
				{
					_userPacketBuffer.data[_userPacketBuffer.length++] = determinePointerType(dataToAdd) | 0xf0;	//Mark that this field has 15 members or more
					_userPacketBuffer.data[_userPacketBuffer.length++] = numberOfElements;
				}
				else
				{
					return(false);	//Not enough space left in the packet
				}
			}
			memcpy(&_userPacketBuffer.data[_userPacketBuffer.length],dataToAdd,numberOfElements*sizeof(dataToAdd[0]));		//Copy in the data
			_userPacketBuffer.length+=numberOfElements*sizeof(dataToAdd[0]);									//Advance the index past the data
			_userPacketBuffer.data[_userPacketFieldCounterIndex] = _userPacketBuffer.data[_userPacketFieldCounterIndex] + 1;	//Increment the field counter
			return(true);
		}
		//Overloaded functions to determine type, should be able to do with decltype or similar but I haven't worked out the syntax
		uint8_t ICACHE_FLASH_ATTR determineType(bool type)		{return(USR_DATA_BOOL		);}
		uint8_t ICACHE_FLASH_ATTR determineType(char type)		{return(USR_DATA_CHAR		);}
		uint8_t ICACHE_FLASH_ATTR determineType(uint8_t type)	{return(USR_DATA_UINT8_T	);}
		uint8_t ICACHE_FLASH_ATTR determineType(int8_t type)	{return(USR_DATA_INT8_T		);}
		uint8_t ICACHE_FLASH_ATTR determineType(uint16_t type)	{return(USR_DATA_UINT16_T	);}
		uint8_t ICACHE_FLASH_ATTR determineType(int16_t type)	{return(USR_DATA_INT16_T	);}
		uint8_t ICACHE_FLASH_ATTR determineType(uint32_t type)	{return(USR_DATA_UINT32_T	);}
		uint8_t ICACHE_FLASH_ATTR determineType(int32_t type)	{return(USR_DATA_INT32_T	);}
		uint8_t ICACHE_FLASH_ATTR determineType(uint64_t type)	{return(USR_DATA_UINT64_T	);}
		uint8_t ICACHE_FLASH_ATTR determineType(int64_t type)	{return(USR_DATA_INT64_T	);}
		uint8_t ICACHE_FLASH_ATTR determineType(float type)		{return(USR_DATA_FLOAT		);}
		uint8_t ICACHE_FLASH_ATTR determineType(double type)	{return(USR_DATA_DOUBLE		);}
		uint8_t ICACHE_FLASH_ATTR determineType(String type)	{return(USR_DATA_STRING		);}
		template<typename typeToDetermine>
		uint8_t ICACHE_FLASH_ATTR determineType(typeToDetermine type)	{return(USR_DATA_UNAVAILABLE);}	//Fall through to 'unknown'
		
		uint8_t ICACHE_FLASH_ATTR determinePointerType(bool* type)		{return(USR_DATA_BOOL		);}
		uint8_t ICACHE_FLASH_ATTR determinePointerType(char* type)		{return(USR_DATA_CHAR		);}
		uint8_t ICACHE_FLASH_ATTR determinePointerType(uint8_t* type)	{return(USR_DATA_UINT8_T	);}
		uint8_t ICACHE_FLASH_ATTR determinePointerType(int8_t* type)	{return(USR_DATA_INT8_T		);}
		uint8_t ICACHE_FLASH_ATTR determinePointerType(uint16_t* type)	{return(USR_DATA_UINT16_T	);}
		uint8_t ICACHE_FLASH_ATTR determinePointerType(int16_t* type)	{return(USR_DATA_INT16_T	);}
		uint8_t ICACHE_FLASH_ATTR determinePointerType(uint32_t* type)	{return(USR_DATA_UINT32_T	);}
		uint8_t ICACHE_FLASH_ATTR determinePointerType(int32_t* type)	{return(USR_DATA_INT32_T	);}
		uint8_t ICACHE_FLASH_ATTR determinePointerType(uint64_t* type)	{return(USR_DATA_UINT64_T	);}
		uint8_t ICACHE_FLASH_ATTR determinePointerType(int64_t* type)	{return(USR_DATA_INT64_T	);}
		uint8_t ICACHE_FLASH_ATTR determinePointerType(float* type)		{return(USR_DATA_FLOAT		);}
		uint8_t ICACHE_FLASH_ATTR determinePointerType(double* type)	{return(USR_DATA_DOUBLE		);}
		uint8_t ICACHE_FLASH_ATTR determinePointerType(String* type)	{return(USR_DATA_STRING		);}

		//Built in peripheral support
		void enableActivityLed(uint8_t,bool);				//Enables an activity LED, argument are the pin and the 'on' state. This blinks on send/receive.
		void enableStatusLed(uint8_t,bool);					//Enables a status LED, arguments are the pin and the 'on' state. This counts out the number of neighbours.

		//Callback functions
		#ifdef ESP8266
		void espNowReceiveCallback(uint8_t*, uint8_t*, uint8_t);	//Callbacks for the espnow library have to be public due to the wrapper function, but we do not expect somebody to call them
		void espNowSendCallback(uint8_t*, uint8_t);
		#elif defined(ESP32)
		void espNowReceiveCallback(const uint8_t* , const uint8_t*, int32_t);
		void espNowSendCallback(const uint8_t*, esp_now_send_status_t);
		#endif


		/* Public functions used for the 'network analyser' sketch
		 *
		 * If building a LARGE application that does not need them they can
		 * be omitted by commenting out the #define m2mMeshIncludeDebugFeatures in m2mMesh.h
		 *
		 */
		#ifdef m2mMeshIncludeMeshInfoFeatures
		//Used for the 'network analyser' sketch
		uint8_t maxNumberOfOriginators();
		uint8_t numberOfNodes(uint8_t);						//Returns the total number of originators in the mesh for this node
		uint8_t numberOfActiveNeighbours();					//Number of active neighbours for this node
		uint8_t numberOfActiveNeighbours(uint8_t);			//Number of active neighbours for another node
		uint8_t nodeId(uint8_t *);							//Finds the ID of an originator from the MAC address or MESH_ORIGINATOR_NOT_FOUND if it isn't found
		bool nodeIsReachable(uint8_t);						//Is a node valid
		void macAddress(uint8_t,uint8_t *);					//Supplies the MAC address of an originator when passed an array
		uint8_t flags(uint8_t id);							//Flags set by the originator
		bool elpIsValid(uint8_t);							//Is ELP up?
		bool ogmIsValid(uint8_t);							//Is OGM up?
		bool nhsIsValid(uint8_t);							//Is NHS up?
		bool validRoute(uint8_t);							//Is there a valid route to a destination
		uint32_t ogmReceived(uint8_t);						//Number of OGMs received
		uint32_t ogmEchoes(uint8_t);						//Number of OGMs echoes received
		uint32_t elpInterval(uint8_t);						//Expected ELP interval
		uint32_t ogmInterval(uint8_t);						//Expected OGM interval
		uint32_t nhsInterval(uint8_t);						//Expected NHS interval
		uint32_t elpLastSeen(uint8_t);						//Last time ELP was seen
		uint32_t ogmLastSeen(uint8_t);						//Last time OGM was seen
		uint32_t nhsLastSeen(uint8_t);						//Last time NHS was seen
		bool actingAsTimeServer();							//Is this node acting as a time server
		bool actingAsTimeServer(uint8_t);					//Is a node acting as a time server
		uint32_t initialFreeHeap(uint8_t);					//Initial free heap of a node
		uint32_t currentFreeHeap(uint8_t);					//Current free heap of a node
		uint32_t largestFreeBlock(uint8_t);					//Current free heap of a node
		uint8_t heapFragmentation(uint8_t);					//Heap fragmentation of a node
		uint32_t sequenceNumber();							//Last sequence for this node
		uint32_t lastSequenceNumber(uint8_t);				//Last sequence number seen from a node
		float supplyVoltage(uint8_t);						//Supply or battery voltage for another node
		uint32_t localTransmissionQuality(uint8_t);			//Local Transmission quality to a node
		uint32_t globalTransmissionQuality(uint8_t);		//Global Transmission quality to a node
		uint8_t selectedRouter(uint8_t);					//Selected router for a destination
		uint16_t serviceFlags();							//Returns current service flags
		void setServiceFlags(uint16_t );					//Sets the service flags
		float currentTxPower();								//Returns current TxPower for this node
		float currentTxPower(uint8_t);						//Returns current TxPower for another node
		float txPowerFloor();								//Returns the current tx power floor
		uint8_t currentMeshTimeServer();					//The node this one is using as a time server
		int32_t meshTimeDrift();							//Returns 'mesh time' drift
		uint32_t rxPackets();								//Stats on received packets
		uint32_t rxPackets(uint8_t);						//Stats on received packets for another node
		uint32_t txPackets();								//Stats on transmitted packets
		uint32_t txPackets(uint8_t);						//Stats on transmitted packets for another node
		uint32_t droppedRxPackets();						//Stats on dropped receive packets
		uint32_t droppedRxPackets(uint8_t);					//Stats on dropped receive packets for another node
		uint32_t droppedTxPackets();						//Stats on dropped transmit packets
		uint32_t droppedTxPackets(uint8_t);					//Stats on dropped transmit packets for another node
		#endif
		
		#ifdef m2mMeshIncludeDebugFeatures
		//Debugging functions
		void enableDebugging(Stream &);						//Start debugging on a Stream, probably Serial but could be elsewhere
		void enableDebugging(Stream &, uint32_t);			//Start debugging on a Stream, probably Serial but could be elsewhere, and change the default logging level
		void enableDebugging();								//Start debugging if previously stopped
		void enableDebugging(uint32_t);						//Start debugging if previously stopped and set a level
		void disableDebugging();							//Stop debugging
		uint32_t loggingLevel();							//Returns current log level
		void setLoggingLevel(uint32_t );					//Sets current log level
		void nodeToLog(uint8_t);							//Sets the node to log
		void logAllNodes();									//Sets the node to log
		static const uint32_t MESH_UI_LOG_ALL_SENT_PACKETS = 1048576ul;
		static const uint32_t MESH_UI_LOG_ALL_RECEIVED_PACKETS = 524288ul;
		static const uint32_t MESH_UI_LOG_WIFI_POWER_MANAGEMENT = 262144ul;
		static const uint32_t MESH_UI_LOG_BUFFER_MANAGEMENT = 131072ul;
		static const uint32_t MESH_UI_LOG_SCANNING = 65536ul;
		static const uint32_t MESH_UI_LOG_PEER_MANAGEMENT = 32768ul;
		static const uint32_t MESH_UI_LOG_USR_SEND = 16384ul;
		static const uint32_t MESH_UI_LOG_USR_RECEIVED = 8192ul;
		static const uint32_t MESH_UI_LOG_USR_FORWARDING = 4096ul;
		static const uint32_t MESH_UI_LOG_NHS_SEND = 2048ul;
		static const uint32_t MESH_UI_LOG_NHS_RECEIVED = 1024ul;
		static const uint32_t MESH_UI_LOG_NHS_FORWARDING = 512ul;
		static const uint32_t MESH_UI_LOG_OGM_SEND = 256ul;
		static const uint32_t MESH_UI_LOG_OGM_RECEIVED = 128ul;
		static const uint32_t MESH_UI_LOG_OGM_FORWARDING = 64ul;
		static const uint32_t MESH_UI_LOG_ELP_SEND = 32ul;
		static const uint32_t MESH_UI_LOG_ELP_RECEIVED = 16ul;
		static const uint32_t MESH_UI_LOG_ELP_FORWARDING = 8ul;
		static const uint32_t MESH_UI_LOG_INFORMATION = 4ul;
		static const uint32_t MESH_UI_LOG_WARNINGS = 2ul;
		static const uint32_t MESH_UI_LOG_ERRORS = 1ul;
		#endif

		static const uint16_t PROTOCOL_USR_FORWARD = 32768;			//Node will forward user data - node will forward user application, essential for a relay but perhaps undesirable on end nodes
		static const uint16_t PROTOCOL_USR_RECEIVE = 16384;			//Node will process user data - node will process user application data, not necessary on some devices
		static const uint16_t PROTOCOL_USR_SEND = 8192;				//Node will send user data - node sends user application data, not necessary on some devices
		static const uint16_t PROTOCOL_NHS_SUPPLY_VOLTAGE = 4096;	//Node will share its power information - useful to check the battery on devices, not essential
		static const uint16_t PROTOCOL_NHS_TIME_SERVER = 2048;		//Node will share its time information	- this maintains a central timestamp across the nodes to help synchronise events
		static const uint16_t PROTOCOL_NHS_INCLUDE_ORIGINATORS		//Node will share originator information - it will forward a list of ALL nodes, speeding global mesh discovery
			= 1024;
		static const uint16_t PROTOCOL_NHS_FORWARD = 512;			//Node will forward NHS data - it will forward information about other nodes, useful for remote troubleshooting
		static const uint16_t PROTOCOL_NHS_RECEIVE = 256;			//Node will process NHS data - it will process information about the health of other nodes, not typically essential
		static const uint16_t PROTOCOL_NHS_SEND = 128;				//Node will send NHS data - it will shares 'health' information about itself
		static const uint16_t PROTOCOL_OGM_FORWARD = 64;			//Node will forward OGM data - it will forward information about how to reach non-local nodes, essential for a functioning mesh
		static const uint16_t PROTOCOL_OGM_RECEIVE = 32;			//Node will process OGM data - it will read information about how to reach non-local nodes
		static const uint16_t PROTOCOL_OGM_SEND = 16;				//Node will send OGM data - it will share routing information about itself with non-local nodes
		static const uint16_t PROTOCOL_ELP_INCLUDE_PEERS = 8;		//Node will share neighbour information - it will share information about its nearby neighbours, speeding local mesh discovery
		static const uint16_t PROTOCOL_ELP_FORWARD = 4;				//Node will forward forward ELP packets - it will forward ELP packets from neighbours, typically this is disabled
		static const uint16_t PROTOCOL_ELP_RECEIVE = 2;				//Node will process ELP packets - it listens for nearby neighbours
		static const uint16_t PROTOCOL_ELP_SEND = 1;				//Node will send ELP packets - it will announce itself to nearby neighbours
		//These should be converted to be compatible with msgpack really but msgpack uses a much more complicated scheme
		static const uint8_t USR_DATA_UNAVAILABLE =    0xff;			//Used to denote no more data left, this is never packed in a packet, but can be returned to the application
		static const uint8_t USR_DATA_BOOL =           0x00;			//Used to denote boolean, it also implies the boolean is false
		static const uint8_t USR_DATA_BOOL_TRUE =      0x01;			//Used to denote boolean, it also implies the boolean is true
		static const uint8_t USR_DATA_UINT8_T =        0x02;			//Used to denote an uint8_t in user data
		static const uint8_t USR_DATA_UINT16_T =       0x03;			//Used to denote an uint16_t in user data
		static const uint8_t USR_DATA_UINT32_T =       0x04;			//Used to denote an uint32_t in user data
		static const uint8_t USR_DATA_UINT64_T =       0x05;			//Used to denote an uint64_t in user data
		static const uint8_t USR_DATA_INT8_T =         0x06;			//Used to denote an int8_t in user data
		static const uint8_t USR_DATA_INT16_T =        0x07;			//Used to denote an int16_t in user data
		static const uint8_t USR_DATA_INT32_T =        0x08;			//Used to denote an int32_t in user data
		static const uint8_t USR_DATA_INT64_T =        0x09;			//Used to denote an int64_t in user data
		static const uint8_t USR_DATA_FLOAT =          0x0a;			//Used to denote a float (32-bit) in user data
		static const uint8_t USR_DATA_DOUBLE =         0x0b;			//Used to denote a double float (64-bit) in user data
		static const uint8_t USR_DATA_CHAR =           0x0c;			//Used to denote a char in user data
		static const uint8_t USR_DATA_STR =            0x0d;			//Used to denote a null terminated C string in user data
		static const uint8_t USR_DATA_STRING =         0x0e;			//Used to denote a String in user data
		static const uint8_t USR_DATA_CUSTOM =         0x0f;			//Used to denote a custom field in user data
		//Return values for arrays, which are packed differently based off their length, this value never packed in a packet
		static const uint8_t USR_DATA_BOOL_ARRAY =     0xf0;			//Used to denote boolean array in user data
		static const uint8_t USR_DATA_UINT8_T_ARRAY =  0xf2;			//Used to denote an uint8_t array in user data
		static const uint8_t USR_DATA_UINT16_T_ARRAY = 0xf3;			//Used to denote an uint16_t array in user data
		static const uint8_t USR_DATA_UINT32_T_ARRAY = 0xf4;			//Used to denote an uint32_t array in user data
		static const uint8_t USR_DATA_UINT64_T_ARRAY = 0xf5;			//Used to denote an uint64_t array in user data
		static const uint8_t USR_DATA_INT8_T_ARRAY =   0xf6;			//Used to denote an int8_t array in user data
		static const uint8_t USR_DATA_INT16_T_ARRAY =  0xf7;			//Used to denote an int16_t array in user data
		static const uint8_t USR_DATA_INT32_T_ARRAY =  0xf8;			//Used to denote an int32_t array in user data
		static const uint8_t USR_DATA_INT64_T_ARRAY =  0xf9;			//Used to denote an int64_t in user data
		static const uint8_t USR_DATA_FLOAT_ARRAY =    0xfa;			//Used to denote a float array (32-bit) in user data
		static const uint8_t USR_DATA_DOUBLE_ARRAY =   0xfb;			//Used to denote a double float array (64-bit) in user data
		static const uint8_t USR_DATA_CHAR_ARRAY =     0xfc;			//Used to denote a char array in user data

	private:
		//High level variables
		uint8_t _currentChannel = 1;						//Mesh channel is set at begin() and should never change
		uint8_t _meshId = B01010101;						//Used to modify checksum
		char *_nodeName = nullptr;							//Node name, set with setNodeName()
		uint8_t _localMacAddress[6];						//Local MAC address
		uint8_t _broadcastMacAddress[6] = 					//Broadcast MAC address
		{0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
		bool _joinedMesh = false;							//Is this node part of an active mesh
		uint32_t _sequenceNumber = 1;						//Sequence number added to every packet
		uint16_t _serviceFlags = 0xffff ^					//Controls which protocols and services this node offers
			(PROTOCOL_NHS_SUPPLY_VOLTAGE |
			PROTOCOL_ELP_FORWARD);
		uint32_t _currentInterval[5];						//Packet sending intervals, per packet type
		uint32_t _lastSent[5];								//Internal timers, per packet type
		uint32_t _currentTtl[5];							//TTLs, per packet type
		uint32_t _meshLastChanged = 0;
		bool _stable = false;								//Is the mesh stable?
		uint32_t _lastHousekeeping = 0;
		const uint32_t _housekeepingInterval = 1000ul;
		bool _waitingForSend = false;						//Are we waiting for a synchronous send?
		bool _sendSuccess = false;							//Store the result of the sending callback
		uint8_t _sendtimer = 0;								//Used in timing out synchronous sends
		uint8_t _sendTimeout = 100;							//Send timeout in ~ms, actually number of loops it waits
		M2MMESH_CALLBACK;									//Function pointer for the callback function

		//Packet buffers
		m2mMeshPacketBuffer _receiveBuffer[M2MMESHRECEIVEBUFFERSIZE];	//Receive buffer for mesh traffic
		uint8_t _receiveBufferIndex = 0;								//Receive buffer index
		uint8_t _processBufferIndex = 0;								//Receive buffer index

		m2mMeshPacketBuffer _applicationBuffer[M2MMESHAPPLICATIONBUFFERSIZE];	//Application data buffer
		uint8_t _applicationBufferWriteIndex = 0;								//Receive buffer index
		uint8_t _applicationBufferReadIndex = 0;								//Receive buffer index

		m2mMeshPacketBuffer _sendBuffer;								//Single send buffer

		//Separate buffer for the user packet
		uint8_t _receivedUserPacketIndex = 0;						//Index during decode
		uint8_t _receivedUserPacketFieldCounter = 0;				//Fields left in packet

		#ifdef m2mMeshIncludeDebugFeatures
		//Debugging variables
		Stream *_debugStream = nullptr;						//Pointer to debugging stream
		bool _debugEnabled = false;							//Whether stream debugging is enabled or not
		#endif

		//Originator related variables
		m2mMeshOriginatorInfo *_originator;					//Pointer to the originator table, which is allocated in the constructor function
		uint8_t _maxNumberOfOriginators = 16;				//The default number of maximum originators. This can be changed at begin(). Set to 0 for automatic allocation of resource, which may cause heap fragmentation and affect stability.
		uint8_t _numberOfOriginators = 0;					//The current number of originators
		static const uint8_t _maxNumberOfPeers = 20;		//The maximum number of ESP-Now peers
		uint32_t _peerLifetime = 60000;						//How long a peering lasts without use, default 60s
		uint8_t _numberOfPeers = 0;							//The current number of ESP-Now peers
		uint8_t _numberOfReachableOriginators = 0;			//The current number of reachable originators
		uint8_t _numberOfActiveNeighbours = 0;				//The current number of nearby active neighbours
		uint8_t _meshMacAddress[6] = {0,0,0,0,0,0};			//A synthetic MAC address XORed from all the members used to indicate stability

		//Global packet flags & values
		static const uint8_t ESP_NOW_MIN_PACKET_SIZE = 64;			//Minimum packet size
		static const uint8_t ESP_NOW_MAX_PACKET_SIZE = 250;			//Maximum packet size
		//static const uint8_t MESH_PROTOCOL_VERSION = 0x01;			//Mesh version
		static const uint8_t NO_FLAGS = 0x00;						//No flags on packet
		static const uint8_t SEND_TO_ALL_NODES = 0x80;				//If in the packet it flags this packet be sent to all ESP-Now nodes and does not include a destination address
		static const uint32_t ANTI_COLLISION_JITTER = 250ul;		//Jitter in milliseconds to try and avoid in-air collisions
		static const uint8_t MESH_ORIGINATOR_NOT_FOUND = 255;		//Signifies that a node is unset or unknown
		static const uint8_t MESH_NO_MORE_ORIGINATORS_LEFT = 254;	//Signifies the mesh is 'full' and no more members can join


		//ELP - Echo Location Protocol packet flags & values
		static const uint8_t ELP_PACKET_TYPE = 0x00;				//The first octet of every ESP-Now packet identifies what it is
		static const uint8_t ELP_DEFAULT_TTL = 0;					//A TTL of >0 means it may be forwarded
		static const uint8_t ELP_DEFAULT_FLAGS = SEND_TO_ALL_NODES;	//Default ELP flags
		static const uint8_t ELP_FLAGS_INCLUDES_PEERS = 0x01;		//Flag set when ELP includes peer information

		static const uint32_t ELP_DEFAULT_INTERVAL = 10000ul;		//How often to send ELP (default every 10s)
		static const uint16_t LTQ_MAX_VALUE = 65535;				//Maximum value for Local Transmit Quality
		static const uint16_t LTQ_STARTING_VALUE = 32768;			//Starting value for Local Transmit Quality given to a new peer

		//OGM - Originator Message packet flags & values
		static const uint8_t OGM_PACKET_TYPE = 0x01;				//The first octet of every ESP-Now packet identifies what it is
		static const uint8_t OGM_DEFAULT_TTL = 50;            		//A TTL of >0 means it may be forwared. OGM MUST be forwarded for a multi-hop mesh to form
		static const uint8_t OGM_DEFAULT_FLAGS = SEND_TO_ALL_NODES;//Default OGM flags
		static const uint32_t OGM_DEFAULT_INTERVAL = 60000ul; 		//How often to send OGM (default every 60s)
		static const uint8_t OGM_HOP_PENALTY = 0x00ff;				//Drop the GTQ in OGM packets before forwarding
		static const uint8_t SEQUENCE_NUMBER_MAX_AGE = 8;			//Used for detection of sequence number resets/rollover

		//NHS - Node Health/Status packet flags & values
		static const uint8_t NHS_PACKET_TYPE = 0x02;          		//The first octet of every ESP-Now packet identifies what it is
		static const uint8_t NHS_DEFAULT_TTL = 50;            		//A TTL of >0 means it may be forwarded.
		static const uint8_t NHS_FLAGS_NODE_NAME_SET = 0x4;			//Flag set when the NHS packet includes a friendly name
		static const uint8_t NHS_FLAGS_INCLUDES_ORIGINATORS = 0x08;	//Flag set when the NHS packet includes peer information
		static const uint8_t NHS_FLAGS_INCLUDES_VCC = 0x10;			//Flag set when the NHS packet includes supply voltage
		static const uint8_t PROCESSOR_ESP8266 = 0x20;				//
		static const uint8_t PROCESSOR_ESP32 =   0x40;				//
		static const uint32_t NHS_DEFAULT_INTERVAL = 300000ul; 		//How often to send NHS (default every 5m)

		#if defined(ESP8266)
		static const uint8_t NHS_DEFAULT_FLAGS = SEND_TO_ALL_NODES | PROCESSOR_ESP8266;	//Default NHS flags
		#elif defined(ESP32)
		static const uint8_t NHS_DEFAULT_FLAGS = SEND_TO_ALL_NODES | PROCESSOR_ESP32;	//Default NHS flags
		#endif
		static const uint8_t NHS_FLAGS_TIMESERVER = 0x01;        	//Flag set when acting as a time server
		#if defined (m2mMeshIncludeRTCFeatures)
		static const uint8_t NHS_FLAGS_RTCSERVER = 0x02;	        	//Flag set when have a source of real time clock
		#endif


		bool _actingAsTimeServer = true;					//Everything starts out as a potential time server, but defers to longer running nodes
		uint8_t _currentMeshTimeServer 						//The current time server
			= MESH_ORIGINATOR_NOT_FOUND;
		int32_t _meshTimeOffset = 0;						//NHS keeps a semi-synced clock to the device with the longest uptime. This is not uber-accurate and may fluctuate slightly!
		int32_t _meshTimeDrift = 0;							//Track clock drift over time, just for info
		bool _meshTimeNegotiated = false;					//This is false until this node has participated in a time server election

		#if defined (m2mMeshIncludeRTCFeatures)
		bool rtc = false;									//Set if an RTC is configured
		bool _actingAsRTCServer = false;					//Even if configured with an RTC, there may be a higher priority time server
		uint8_t _currentRTCServer	 						//The current RTC server
			= MESH_ORIGINATOR_NOT_FOUND;
		struct tm timeinfo;									//Time data structure for RTC
		uint32_t epochOffset = 0;							//Used to infer epoch time from mesh time
		char* timezone = nullptr;							//Timezone string
		#endif

		uint32_t _initialFreeHeap = ESP.getFreeHeap();		//Used to get a percentage value for free heap
		uint32_t _currentFreeHeap = _initialFreeHeap;		//Monitor free heap
		uint32_t _rxPackets = 0;							//Monitor received packets
		uint32_t _txPackets = 0;							//Monitor sent packets
		uint32_t _droppedRxPackets = 0;						//Monitor rcv buffer receive problems
		uint32_t _droppedTxPackets = 0;						//Monitor rcv buffer send problems
		uint32_t _droppedAppPackets = 0;					//Monitor app buffer receive problems

		//USR - User data packet flags and values
		const uint8_t USR_PACKET_TYPE = 0x03;				//The first octet of every ESP-Now packet identifies what it is
		const uint8_t USR_DEFAULT_TTL = 50;					//A TTL of >0 means it may be forwared.
		const uint8_t USR_DEFAULT_FLAGS = SEND_TO_ALL_NODES;
		const uint8_t USR_MAX_PACKET_SIZE = 250;			//Maximum packet size for user data
		const uint32_t USR_DEFAULT_INTERVAL = 1000;			//How often to send low priority user data

		//FSP - File Sync Protocol, for SDFat filesystem
		const uint8_t FSP_PACKET_TYPE = 0x04;				//The first octet of every ESP-Now packet identifies what it is
		const uint8_t FSP_DEFAULT_TTL = 50;					//A TTL of >0 means it may be forwared. OGM MUST be forwarded for a multi-hop mesh to form
		const uint8_t FSP_DEFAULT_FLAGS = SEND_TO_ALL_NODES;//Not yet implemented
		const uint32_t FSP_DEFAULT_INTERVAL = 1000;			//How often to send low priority file sync data

		//Power management & sleep related variables
		const uint32_t POWER_MANAGEMENT_INTERVAL = 10000;	//How often to adjust the Wi-Fi Tx power
		const uint32_t FLOOR_MANAGEMENT_INTERVAL = 300000;	//How often we review the power floor (5m)
		const float MIN_TX_POWER = 0.0f;					//Minimum Tx power. THis is multiplied by four internally by the Wi-Fi library so 0-20.5 is actually 0-82dBm
		const float MAX_TX_POWER = 20.5f;					//Maximum Tx power
		const float VCC_HIGH_THRESHOLD = 3.6f;				//High voltage that triggers an out of bounds warning
		const float VCC_LOW_THRESHOLD = 3.0f;				//Low voltage that triggers an out of bounds warning

		bool _powerManagementEnabled = true;

		float _currentTxPower = MAX_TX_POWER;				//Always start at maximum power to help with joining the mesh
		float _txPowerFloor = MIN_TX_POWER;					//We find a 'floor' on the TX power to stop nodes oscillating in and out of packet loss
		uint32_t _txPowerFloorTimer = 0;					//How often this node reconsiders the power floor
		uint32_t _powerManagementTimer = 0;					//Don't do power management until there's been enough time to pick up and settle some peers

		//Time syncing functions
		void _updateMeshTime(uint32_t, uint8_t);			//Updates the time from an advertising time server
		void _setMeshTime(uint32_t, uint8_t);
		void _chooseNewTimeServer();						//If the current time server disappears, try to pick a new one
		void _becomeTimeServer();
		
		//ESP-NOW related functions in many of these there are lots of preprocessor directives to handle API differences between ESP8266/8285 and ESP32 at compile time
		bool _initESPNow();											//Initialises ESP-NOW
		uint8_t _calculateChecksum(m2mMeshPacketBuffer &);			//Calculate checksum
		void _addChecksum(m2mMeshPacketBuffer &);					//Adds the checksum to packet
		bool _checksumCorrect(m2mMeshPacketBuffer &);				//Checks the checksum
		bool _routePacket(m2mMeshPacketBuffer &, bool wait = true);	//Route and send a user packet
		bool _sendPacket(m2mMeshPacketBuffer &, bool wait = true);	//Sends ESP-NOW from a packet buffer, optional wait parameter is whether to wait for confirmation or not
		bool _addPeer(uint8_t* mac, uint8_t peerChannel);			//Add a peer
		bool _removePeer(uint8_t originatorId);						//Remove peer
		/*
		#if defined(ESP8266)
		uint8_t _sendPacket(m2mMeshPacketBuffer &, bool wait = true);	//Sends ESP-NOW from a packet buffer, optional wait parameter is whether to wait for confirmation or not
		#elif defined(ESP32)
		esp_err_t _sendPacket(m2mMeshPacketBuffer &, bool wait = true);	//Sends ESP-NOW from a packet buffer, optional wait parameter is whether to wait for confirmation or not
		#endif
		*/
		//Originator management functions
		uint8_t _originatorIdFromMac(uint8_t *);			//Finds the ID of an originator from the MAC address or MESH_ORIGINATOR_NOT_FOUND if it isn't found
		uint8_t _originatorIdFromMac(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
		uint8_t _addOriginator(uint8_t *,uint8_t);			//Adds an originator given the MAC address and channel
		void _calculateLtq(uint8_t);						//Calculates the LTQ for a node
		bool _isLocalMacAddress(uint8_t *);					//Checks if a MAC address is the local one

		//Routing protocol functions
		bool _sendElp(m2mMeshPacketBuffer &);						//Send ELP with default settings
		bool _sendElp(bool, m2mMeshPacketBuffer &);				//Send ELP with or without peers
		bool _sendElp(uint8_t, m2mMeshPacketBuffer &);				//Send ELP with specific TTL
		bool _sendElp(bool,uint8_t, m2mMeshPacketBuffer &);		//Send ELP with or without peers and specific TTL
		void _processElp(uint8_t, uint8_t, m2mMeshPacketBuffer &);	//Process incoming ELP payload


		bool _sendOgm(m2mMeshPacketBuffer &);						//Send OGM with default settings
		void _processOgm(uint8_t, uint8_t, m2mMeshPacketBuffer &);	//Process incoming OGM payload

		bool _sendNhs(m2mMeshPacketBuffer &);						//Send NHS with default settings, using the supplied buffer to build the packet
		void _processNhs(uint8_t, uint8_t, m2mMeshPacketBuffer &);	//Process incoming NHS payload
		
		void _processUsr(uint8_t, uint8_t, m2mMeshPacketBuffer &);	//Process incoming USR payload

		void _processPacket(m2mMeshPacketBuffer &);				//Process packet headers and handle forwarding
		bool _dataIsValid(uint8_t, uint8_t);				//Is a particular protocol up?
		void _originatorHasBecomeRoutable(uint8_t);
		void _originatorHasBecomeUnroutable(uint8_t);

		//Status LED
		const uint32_t STATUS_LED_BLINK_TIME = 25ul;		//How long the status LED is on
		const uint32_t STATUS_LED_PAUSE_TIME = 300ul;		//How long between flashes
		const uint32_t STATUS_LED_FREQUENCY = 10000ul;		//How frequently the status is signalled
		bool _statusLedEnabled = false;						//Is the status LED enabled?
		bool _statusLedState = false;						//Is the status LED lit?
		uint8_t _statusLedPin = 0;							//The status LED pin
		bool _statusLedOnState = HIGH;						//The pin state when the LED is lit
		uint32_t _statusLedTimer = 0;						//Used to synchronise the status LEDs
		uint8_t _statusLedCount = 0;						//Flash counter

		//Activity LED
		const uint32_t ACTIVITY_LED_BLINK_TIME = 10ul;		//How long the activity LED is on
		bool _activityLedEnabled = false;					//Is the activity LED enabled?
		bool _activityLedState = false;						//Is the activity LED lit?
		uint8_t _activityLedPin = 0;						//The activity LED pin
		bool _activityLedOnState = HIGH;					//The pin state when the LED is lit
		uint32_t _activityLedTimer = 0;						//Used to hold the LED on for a fixed time
		void _blinkActivityLed();							//Function switches on activity LED

		//User data related variables
		//uint8_t _userPacketIndex = 0;								//Current position in the user packet
		uint8_t _userPacketFieldCounterIndex = 0;					//The index where the field count is
		//uint8_t _userPacket[ESP_NOW_MAX_PACKET_SIZE];				//The user packet
		m2mMeshPacketBuffer _userPacketBuffer;						//The user packet
		
		bool _buildingUserPacket = false;													//Are we building a user data packet? Mustn't do it twice
		void _buildUserPacketHeader();														//Create the user packet header for a broadcast packet
		void _buildUserPacketHeader(uint8_t);												//Create the user packet header based off a station ID
		void _buildUserPacketHeader(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);	//Create the user packet header based off a MAC address
		uint8_t _packingOverhead(uint8_t);													//The size of the packing overhead for the current field
		uint8_t _numberOfPackedItems(uint8_t, uint8_t);										//Number of items of a specific type in a field
		
		//Debugging related functions
		#ifdef m2mMeshIncludeDebugFeatures
		uint32_t _loggingLevel = MESH_UI_LOG_INFORMATION | MESH_UI_LOG_WARNINGS | MESH_UI_LOG_ERRORS | MESH_UI_LOG_PEER_MANAGEMENT;
		uint8_t _nodeToLog = MESH_ORIGINATOR_NOT_FOUND;
		#if defined(ESP8266)
		void _errorDescription(uint8_t);					//Prints an error description
		#elif defined(ESP32)
		void _errorDescription(esp_err_t);
		#endif
		#ifdef ESP8266
		//void _debugPacket(uint8_t *, uint8_t *, uint8_t); //Decode incoming packet for debugging purpose
		void _debugPacket(m2mMeshPacketBuffer &); //Decode incoming packet for debugging purpose
		#elif defined(ESP32)
		//void _debugPacket(const uint8_t *, const uint8_t *, int32_t);
		void _debugPacket(m2mMeshPacketBuffer &);
		#endif
		void _friendlyUptime(uint32_t, char *);				//Formats uptime as a duration string
		void _packetTypeDescription(char*,uint8_t);			//Formats a packet type into a char array
		#endif

		
};

extern m2mMeshClass m2mMesh;	//Create an instance of the class, as only one is practically usable at a time
#endif