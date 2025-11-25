using System;

namespace MSCL_Displacement_Example_CSharp
{
    class Example1
    {
        public static void getCurrentConfig(mscl.DisplacementNode node)
        {
            mscl.LinearEquation cals = node.getAnalogToDisplacementCal();
            Console.WriteLine("Analog to Displacement Cal: Slope: " + cals.slope() + " Offset: " + cals.offset());

            Console.WriteLine("Output Data Rate: " + node.getDisplacementOutputDataRate().prettyStr());
        }
    }
}