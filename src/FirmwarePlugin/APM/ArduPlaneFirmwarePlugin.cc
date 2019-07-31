/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "ArduPlaneFirmwarePlugin.h"

bool ArduPlaneFirmwarePlugin::_remapParamNameIntialized = false;
FirmwarePlugin::remapParamNameMajorVersionMap_t ArduPlaneFirmwarePlugin::_remapParamName;

APMPlaneMode::APMPlaneMode(uint32_t mode, bool settable)
    : APMCustomMode(mode, settable)
{
    QMap<uint32_t,QString> enumToString;
    enumToString.insert(MANUAL,         QObject::tr("Manual"));
    enumToString.insert(CIRCLE,         QObject::tr("Circle"));
    enumToString.insert(STABILIZE,      QObject::tr("Stabilize"));
    enumToString.insert(TRAINING,       QObject::tr("Training"));
    enumToString.insert(ACRO,           QObject::tr("Acro"));
    enumToString.insert(FLY_BY_WIRE_A,  QObject::tr("FBW A"));
    enumToString.insert(FLY_BY_WIRE_B,  QObject::tr("FBW B"));
    enumToString.insert(CRUISE,         QObject::tr("Cruise"));
    enumToString.insert(AUTOTUNE,       QObject::tr("Autotune"));
    enumToString.insert(AUTO,           QObject::tr("Auto"));
    enumToString.insert(RTL,            QObject::tr("RTL"));
    enumToString.insert(LOITER,         QObject::tr("Loiter"));
    enumToString.insert(GUIDED,         QObject::tr("Guided"));
    enumToString.insert(INITIALIZING,   QObject::tr("Initializing"));
    enumToString.insert(QSTABILIZE,     QObject::tr("QuadPlane Stabilize"));
    enumToString.insert(QHOVER,         QObject::tr("QuadPlane Hover"));
    enumToString.insert(QLOITER,        QObject::tr("QuadPlane Loiter"));
    enumToString.insert(QLAND,          QObject::tr("QuadPlane Land"));
    enumToString.insert(QRTL,           QObject::tr("QuadPlane RTL"));

    setEnumToStringMapping(enumToString);
}

ArduPlaneFirmwarePlugin::ArduPlaneFirmwarePlugin(void)
{
    QList<APMCustomMode> supportedFlightModes;
    supportedFlightModes << APMPlaneMode(APMPlaneMode::MANUAL          ,true);
    supportedFlightModes << APMPlaneMode(APMPlaneMode::CIRCLE          ,true);
    supportedFlightModes << APMPlaneMode(APMPlaneMode::STABILIZE       ,true);
    supportedFlightModes << APMPlaneMode(APMPlaneMode::TRAINING        ,true);
    supportedFlightModes << APMPlaneMode(APMPlaneMode::ACRO            ,true);
    supportedFlightModes << APMPlaneMode(APMPlaneMode::FLY_BY_WIRE_A   ,true);
    supportedFlightModes << APMPlaneMode(APMPlaneMode::FLY_BY_WIRE_B   ,true);
    supportedFlightModes << APMPlaneMode(APMPlaneMode::CRUISE          ,true);
    supportedFlightModes << APMPlaneMode(APMPlaneMode::AUTOTUNE        ,true);
    supportedFlightModes << APMPlaneMode(APMPlaneMode::AUTO            ,true);
    supportedFlightModes << APMPlaneMode(APMPlaneMode::RTL             ,true);
    supportedFlightModes << APMPlaneMode(APMPlaneMode::LOITER          ,true);
    supportedFlightModes << APMPlaneMode(APMPlaneMode::GUIDED          ,true);
    supportedFlightModes << APMPlaneMode(APMPlaneMode::INITIALIZING    ,false);
    supportedFlightModes << APMPlaneMode(APMPlaneMode::QSTABILIZE      ,true);
    supportedFlightModes << APMPlaneMode(APMPlaneMode::QHOVER          ,true);
    supportedFlightModes << APMPlaneMode(APMPlaneMode::QLOITER         ,true);
    supportedFlightModes << APMPlaneMode(APMPlaneMode::QLAND           ,true);
    supportedFlightModes << APMPlaneMode(APMPlaneMode::QRTL            ,true);
    setSupportedModes(supportedFlightModes);

    if (!_remapParamNameIntialized) {
        FirmwarePlugin::remapParamNameMap_t& remapV3_8 = _remapParamName[3][8];

        remapV3_8["SERVO5_FUNCTION"] = QStringLiteral("RC5_FUNCTION");
        remapV3_8["SERVO6_FUNCTION"] = QStringLiteral("RC6_FUNCTION");
        remapV3_8["SERVO7_FUNCTION"] = QStringLiteral("RC7_FUNCTION");
        remapV3_8["SERVO8_FUNCTION"] = QStringLiteral("RC8_FUNCTION");
        remapV3_8["SERVO9_FUNCTION"] = QStringLiteral("RC9_FUNCTION");
        remapV3_8["SERVO10_FUNCTION"] = QStringLiteral("RC10_FUNCTION");
        remapV3_8["SERVO11_FUNCTION"] = QStringLiteral("RC11_FUNCTION");
        remapV3_8["SERVO12_FUNCTION"] = QStringLiteral("RC12_FUNCTION");
        remapV3_8["SERVO13_FUNCTION"] = QStringLiteral("RC13_FUNCTION");
        remapV3_8["SERVO14_FUNCTION"] = QStringLiteral("RC14_FUNCTION");

        remapV3_8["SERVO5_MIN"] = QStringLiteral("RC5_MIN");
        remapV3_8["SERVO6_MIN"] = QStringLiteral("RC6_MIN");
        remapV3_8["SERVO7_MIN"] = QStringLiteral("RC7_MIN");
        remapV3_8["SERVO8_MIN"] = QStringLiteral("RC8_MIN");
        remapV3_8["SERVO9_MIN"] = QStringLiteral("RC9_MIN");
        remapV3_8["SERVO10_MIN"] = QStringLiteral("RC10_MIN");
        remapV3_8["SERVO11_MIN"] = QStringLiteral("RC11_MIN");
        remapV3_8["SERVO12_MIN"] = QStringLiteral("RC12_MIN");
        remapV3_8["SERVO13_MIN"] = QStringLiteral("RC13_MIN");
        remapV3_8["SERVO14_MIN"] = QStringLiteral("RC14_MIN");

        remapV3_8["SERVO5_MAX"] = QStringLiteral("RC5_MAX");
        remapV3_8["SERVO6_MAX"] = QStringLiteral("RC6_MAX");
        remapV3_8["SERVO7_MAX"] = QStringLiteral("RC7_MAX");
        remapV3_8["SERVO8_MAX"] = QStringLiteral("RC8_MAX");
        remapV3_8["SERVO9_MAX"] = QStringLiteral("RC9_MAX");
        remapV3_8["SERVO10_MAX"] = QStringLiteral("RC10_MAX");
        remapV3_8["SERVO11_MAX"] = QStringLiteral("RC11_MAX");
        remapV3_8["SERVO12_MAX"] = QStringLiteral("RC12_MAX");
        remapV3_8["SERVO13_MAX"] = QStringLiteral("RC13_MAX");
        remapV3_8["SERVO14_MAX"] = QStringLiteral("RC14_MAX");

        remapV3_8["SERVO5_REVERSED"] = QStringLiteral("RC5_REVERSED");
        remapV3_8["SERVO6_REVERSED"] = QStringLiteral("RC6_REVERSED");
        remapV3_8["SERVO7_REVERSED"] = QStringLiteral("RC7_REVERSED");
        remapV3_8["SERVO8_REVERSED"] = QStringLiteral("RC8_REVERSED");
        remapV3_8["SERVO9_REVERSED"] = QStringLiteral("RC9_REVERSED");
        remapV3_8["SERVO10_REVERSED"] = QStringLiteral("RC10_REVERSED");
        remapV3_8["SERVO11_REVERSED"] = QStringLiteral("RC11_REVERSED");
        remapV3_8["SERVO12_REVERSED"] = QStringLiteral("RC12_REVERSED");
        remapV3_8["SERVO13_REVERSED"] = QStringLiteral("RC13_REVERSED");
        remapV3_8["SERVO14_REVERSED"] = QStringLiteral("RC14_REVERSED");

        remapV3_8["ARMING_VOLT_MIN"] = QStringLiteral("ARMING_MIN_VOLT");
        remapV3_8["ARMING_VOLT2_MIN"] = QStringLiteral("ARMING_MIN_VOLT2");

        FirmwarePlugin::remapParamNameMap_t& remapV3_10 = _remapParamName[3][10];

        remapV3_10["BATT_ARM_VOLT"] =    QStringLiteral("ARMING_VOLT_MIN");
        remapV3_10["BATT2_ARM_VOLT"] =   QStringLiteral("ARMING_VOLT2_MIN");

        _remapParamNameIntialized = true;
    }
}

int ArduPlaneFirmwarePlugin::remapParamNameHigestMinorVersionNumber(int majorVersionNumber) const
{
    // Remapping supports up to 3.10
    return majorVersionNumber == 3 ? 10 : Vehicle::versionNotSetValue;
}
