#include <string>
using namespace std;

/*
 Project 3 - Part 1 / 5
Video:  Chapter 2 Part 5
 User-Defined Types

 Create a branch named Part1

 Purpose: The entire purpose of this 5-part project is to get you writing C++ code that compiles and to reinforce the syntax habits that C++ requires.  What you create in this project will be used as the basis of Project 5 in the course.   
 
 1) write 10 user-defined types, each with a random number of member variables
    make the member variables have names that are related to type of work the UDT would perform.
    see the example below for clarity on this instruction
 
 2) give the member variables relevant data types
 
 3) add at least 2 member functions to each of your 10 types.  
    make the function parameter list for those member functions use some of your User-Defined Types
    You'll write definitions in part2 for these functions
    you'll call each of these functions in part3
 
 4) make 2 of the 10 user-defined types have a nested class.  this nested class also needs member functions.
 
 5) One of your 10 UDTs should only use UDTs for its member variable types.   
     No primitives allowed!
 
 6) After you finish defining each type, click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

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
struct Filter
{
    string type = "Steiner-Parker";
	int order = 2;
};
/*
 2)
 */
struct SendAndReturn
{
	bool isMono = false;
	unsigned short destination;
	float gainLeftChannel;
	float gainRightChannel;
};
/*
 3) //this is the one only using my defined types
 */ 
struct FilterSection
{
	Filter HP;
	Filter MID;
	Filter LOP;
};
/*
 4)
 */
struct MixerChannel
{
	struct HighPassFilter
	{
		bool isOn;
	};
	int number;
	SendAndReturn sendAndReturn;
	float inputGain = 0;
	float outputGain = 0;
	float pan = 0.5;
	
	void mute(bool muteButton);
	void solo(bool soloButton, int channelNumber);
};
/*
 5)
 */
struct MonoChannel
{
	MixerChannel channel;
	FilterSection filter;
	SendAndReturn sendAndReturn;
};
/*
 6)
 */
struct StereoChannel
{
	MixerChannel leftChannel;
	MixerChannel righChannel;
	SendAndReturn sendAndReturn;	
};
/*
 7)
 */
struct Effect
{
	string name;
	unsigned short number;
	float param1;
	float param2;
};
/*
 8)
 */
struct outputChannel
{
	string name;
	float gain;
	void setGain(float gain);
};
/*
 9)
 */
struct Mixer
{
		Mixer(unsigned short numberOfMonoChannels, unsigned short numberOfStereoChannels)
	{
		for(int i = 0; i<numberOfMonoChannels; i++)
		{
			//i don't understand why i cannot create a new instance of MonoChannel like: 
			//monoChannels[i] = new MonoChannel; //help needed
		}

	
		for(int i = 0; i<numberOfStereoChannels; i++)
		{
			//same here; looking forward to learning about these
			//stereoChannels[i] = new StereoChannel;	

		}
		
	}
	
	MonoChannel monoChannels[4];
	StereoChannel stereoChannels[2];
	//wish i could do this 
	//MonoChannel monoChannels[numberOfMonoChannels];
	//StereoChannel stereoChannels[numberOfStereoChannels];
	Effect effect1;
	Effect effect2;
	
	outputChannel mainMix;
	outputChannel ctrlRoom;

};
/*
10)
*/
struct Wavetable //well, this one is an outlier
{
	string name = "blank";
	float samples[256];
	
	void getCurrentSample(float samples[]);
	void applyEffect(Effect effect); // 3
};
#include <iostream>
int main()
{
    std::cout << "good to go!" << std::endl;
}
