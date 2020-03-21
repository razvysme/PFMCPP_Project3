 #include <string>
 /*
 Project 3 - Part 2 / 5
 Video: Chapter 2 Part 6
 Implementations tasks
 
Create a branch named Part2

 tasks
 1) write the definition for the Type that leftFoot and rightFoot are instantiations of.
    don't forget to define and implement the member functions 'stepForward()' and 'stepSize()'
    you should be able to deduce the return type of those functions based on their usage in Person::run()
    You'll need to insert the Person struct from the video in the space below.
 */

struct Foot
{
    int oldFootPos, newFootPos;
    int howFast;
 
    void stepForward()
    {
        newFootPos = oldFootPos * howFast;
    }
    int stepSize()
    {
        return newFootPos - oldFootPos;
    }
};

struct Person
{
    int age;
    int height;
    float hairLength;
    float GPA;
    unsigned int SATScore;
    Foot leftFoot;
    Foot rightFoot;
    int distanceTraveled;

    void run(int howFast, bool startWithLeftFoot);
};

void Person::run(int howFast, bool startWithLeftFoot)
{
    //howFast is not in use, but i assume it could be a parameter for stepForward function, right? 

    if(startWithLeftFoot == true)
    {
        leftFoot.stepForward();
        rightFoot.stepForward();
    }
    else
    {
        rightFoot.stepForward();
        rightFoot.stepForward();
    }
    distanceTraveled += leftFoot.stepSize() + rightFoot.stepSize();
}

 /*
 2) provide implementations for the member functions you declared in your 10 user-defined types from the previous video outside of your UDT definitions.
 
 3) be sure to write the correct full qualified name for the nested type's member functions.
 
 4) After you finish defining each type/function, click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */
/*
 1)
 */
struct Effect
{
	std::string name;
	unsigned short number;
	float param1;
	float param2;

    void savePresset( float param1, float param2, float effectNumber, std::string userName );
    void changePresset( float param1, float param2 );
};
/*
 2)
 */
struct Filter
{
    std::string type = "Steiner-Parker";
	int order = 2;

    std::string changeType( std::string currentType );
    void bypass();
};
/*
 3)
 */
struct SendAndReturn
{
	bool isMono = false;
	unsigned short destination;
	float gainLeftChannel;
	float gainRightChannel;

    void filter( Filter lowPass );
    void applyEffect( Effect effect );

};
/*
 4) //this is the one only using my defined types
 */ 
struct FilterSection
{
	Filter HP;
	Filter MID;
	Filter LOP;

    int changeOrder( Filter filter );
    void bypass();
};
/*
 5)
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
	
	void mute( bool muteButton );
	void solo( bool soloButton, int channelNumber );
};
/*
 6)
 */
struct MonoChannel
{
	MixerChannel channel;
	FilterSection filter;
	SendAndReturn sendAndReturn;

    void send( MixerChannel channel );
    void mute();
};
/*
 7)
 */
struct StereoChannel
{
	MixerChannel leftChannel;
	MixerChannel righChannel;
	SendAndReturn sendAndReturn;	

    void send( MixerChannel channel );
    void mute();
};
/*
 8)
 */
struct outputChannel
{
	std::string name;
	float gain;
	void setGain( float gain );
    void sendToHeadphone( MixerChannel headphones );
};
/*
 9)
 */
struct Mixer
{
	Mixer( unsigned short numberOfMonoChannels, unsigned short numberOfStereoChannels )
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

    void boot();
    void sendTestSignal( MixerChannel destinationChannel);


};
/*
10)
*/
struct Wavetable //well, this one is an outlier
{
	std::string name = "blank";
	float samples[256];
	
	void getCurrentSample(float samples[]);
	void applyEffect(Effect effect); // 3
};
#include <iostream>
int main()
{
    std::cout << "good to go!" << std::endl;
}


