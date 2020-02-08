/*
 Project 3 - Part 1 / 5
Video:  Chapter 2 Part 5
 User-Defined Types

 Create a branch named Part1
 
 1) write 10 user-defined types, each with a random number of member variables
    try to make the member variables have names that are related to the user-defined type.
 
 2) give the member variables relevant data types
 
 3) add a couple member functions.  
    make the function parameter list for those member functions use some of your User-Defined Types
 
 4) make 2 of the 10 user-defined types be nested class
 
 5) One of your UDTs should only use UDTs for its member variable types.   
     No primitives allowed!
 
 6) After you finish defining each type, click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 Send me the the link to your repl.it in a DM on Slack

 Wait for my code review.
 */

/*
 example:
 */
struct CarWash            //1) a U.D.T. with a random number of member variables
{
    int numSponges = 3;
    double amountOfSoapUsedPerCar = 2.6; //2) relevant data types
    unsigned int numCarsProcessed = 0;
    
    struct Car                             //4) nested class
    {
        bool isAPickupTruck = false;
        float gasMileage = 26.2f;        //2) relevant data types
    };
    
    void washAndWaxCar( Car car );         //3) member function with a user-defined type as the parameter.  The user-defined type parameter happens to be the nested class.
    
    Car myCar;  //5) a member variable whose type is a UDT.
};


/*
 1)
 */
struct Wavetable //well, this one is an outlier
{
	string name = "blank";
	float samples[256];
	
	void getCurrentSample(float samples[]);
}
/*
 2)
 */
struct Filter
{
	string type = "Steiner-Parker";
	int order = 2;
}
/*
 3)
 */
struct SendAndReturn()
{
	bool isMono = false;
	
	int destination;
	float gainLeftChannel;
	float gainRightChannel;
}
/*
 4)
 */
struct FilterSection
{
	Filter HP;
	Filter MID;
	Filter LOP;
}
/*
 5)
 */
struct MixerChannel
{
	struct HighPassFilter
	{
		bool isOn;
	}
	int number;
	SendAndReturn sendAndReturn;
	float inputGain = 0;
	float outputGain = 0;
	float pan = 0.5;
	
	void mute(bool muteButton);
	void solo(bool soloButton, int channelNumber);
}
/*
 6)
 */
struct MonoChannel
{
	MixerChannel channel;
	FilterSection filter;
	SendAndReturn sendAndReturn;
}
/*
 7)
 */
struct StereoChannel
{
	MixerChannel leftChannel;
	MixerChannel righChannel;
	SendAndReturn sendAndReturn;	
}
/*
 8)
 */
struct Effect
{
	string name;
	int number;
	float param1;
	float param2;
}
/*
 9)
 */
struct outputChannel;
{
	string name;
	float gain;
}
/*
 10)
 */
Struct Mixer
{
		Mixer(float numberOfMonoChannels, float numberOfStereoChannels)
	{
		for(int i = 0; i<numberOfMonoChannels, i++)
		monoChannels[i] = MonoChannel;
	
		for(int i = 0; i<numberOfStereoChannelsChannels, i++)
		stereoChannels[i] = StereoChannel;	
	}
	
	int numberOfMonoChannels = 6;
	int numberOfStereoChannel = 2;
	MonoChannel monoChannels[numberOfMonoChannels];
	StereoChannel stereoChannels[numberOfStereoChannels];
	Effect effect1;
	Effect effect2;
	
	outputChannel mainMix;
	outputChannel ctrlRoom;

}
#include <iostream>
int main()
{
    std::cout << "good to go!" << std::endl;
}
