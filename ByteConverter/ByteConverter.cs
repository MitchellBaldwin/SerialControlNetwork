using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace StructByteConverter
{
    public class StructByteConverter
    {
        public static byte[] getByteArray(object structure)
        {
            int payloadSize = Marshal.SizeOf(structure);
            byte[] payloadByteArray = new byte[payloadSize];
            IntPtr ptr = Marshal.AllocHGlobal(payloadSize);

            Marshal.StructureToPtr(structure, ptr, true);
            Marshal.Copy(ptr, payloadByteArray, 0, payloadSize);
            Marshal.FreeHGlobal(ptr);

            return payloadByteArray;
        }

        public static T fromBytes<T>(byte[] payloadByteArray)
        {
            T structure = default(T);

            int payloadSize = Marshal.SizeOf(structure);
            IntPtr ptr = Marshal.AllocHGlobal(payloadSize);

            Marshal.Copy(payloadByteArray, 0, ptr, payloadSize);

            structure = (T)Marshal.PtrToStructure(ptr, structure.GetType());
            Marshal.FreeHGlobal(ptr);

            return structure;
        }
    }
}
