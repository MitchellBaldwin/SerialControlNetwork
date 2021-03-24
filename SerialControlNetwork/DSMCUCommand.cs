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
}