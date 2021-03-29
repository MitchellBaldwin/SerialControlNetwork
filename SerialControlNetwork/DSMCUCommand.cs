using System;

namespace SerialControlNetwork
{
    public struct DSMCUCommand
    {
        public Int16 Speed;
        public Int16 TurnRate;
        public UInt16 STThetaXY;
        public UInt16 STThetaZX;
    }

    public struct DSMCUStatus
    {
        public Int16 VSupply;
        public Int16 LMotorCurrent;
        public Int16 RMotorCurrent;
        public Int16 LActuatorSpeed;
        public Int16 RActuatorSpeed;
    }
}