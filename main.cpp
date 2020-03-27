/*
 Project 3 - Part 4 / 5
 video: Chapter 2 - Part 9
 Member initialization tasks

 Create a branch named Part4
 
 1) initialize some of your member variables either in-class or in the Constructor member initializer list.

 2) make some of your member functions use those initialized member variables via std::cout statements.
 
 3) click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */

#include <iostream>
namespace Example {
struct UDT  
{
    int a; //a member variable
    float b { 2.f }; //3) in-class initialization
    UDT() : a(0) { } //3) 'constructor-initializer-list' member variable initialization
    void printThing()  //the member function
    {
        std::cout << "UDT::printThing() a:" << a << " b: " << b << std::endl;  //4) printing out something interesting
    }
};

int main()
{
    UDT foo; //instantiating a Foo in main()
    foo.printThing(); //calling a member function of the instance that was instantiated.
    return 0;
}
}

//call Example::main()


/*
 1)
 */
struct Effect
{
	std::string name;
	unsigned short number;
	float param1;
	float param2;

    // had to add this struct so my effect logic makes sense
    struct Preset 
    {
        float param1, param2, effectNumber;
        Preset()
        {
            std::cout << "Preset loaded" << std::endl;
        }
    };
    Preset myPresset;

       //constructor
    Effect() 
    {
        param1 = 0; 
        param2 = 0;
        std::cout << "Effect created, parameters initialized to: " << param1 <<std::endl;
    }

    void savePreset( float currentParam1, float currentParam2, float effectNumber, Preset presetName);
    void changePreset( float currentParam1, float currentParam2 );
};

void Effect::savePreset( float currentParam1, float currentParam2, float effectNumber, Preset presetName)
{
    presetName.param1 = currentParam1;
    presetName.param2 = currentParam2;
    presetName.effectNumber = effectNumber;
    std::cout << "Preset " << presetName.effectNumber << " is saved!" << std::endl; 
}
void Effect::changePreset(float currentParam1, float currentParam2)
{
    param1 = currentParam1; //this is some getto getter/setter thing, right?
    param2 = currentParam2;
}
/*
 2)
 */
struct Filter
{
    std::string type;
    int order;
    bool bypassLED = false;
    float cutoff;

    //constructor
    Filter()
    {
        if(order==2)
            type = "Steiner-Parker";
        else
            type = "Ladder";
    }

    std::string changeType( std::string currentType );
    void bypass();
};

std::string Filter::changeType( std::string currentType )
{
    return currentType;
}

void Filter::bypass()
{
    //well this is kinda hard to implement without the audio stream, but it would look something like y[n]=x[n], therefore i added the bypassLED bool so this declaration is not empty.
    bypassLED = true;
}
/*
 3)
 */
struct SendAndReturn
{
    bool isMono = false;
    unsigned short destination;
    float gainLeftChannel;
    float gainRightChannel;

    //constructor
    SendAndReturn()
    {
        gainLeftChannel = 0.0f;
        gainRightChannel = 0.0f;
    }

    void filter( Filter lowPass );
    void applyEffect( Effect effect );
};

void SendAndReturn::filter( Filter lowPass )
{
    lowPass.type="Low Pass"; 
}

void SendAndReturn::applyEffect( Effect effect )
{
    // again, hard to do without audio stream... kinda regret my decisions now :)
    effect.param1 = 1.0f;
    effect.param2 = 1.0f;
}
/*
 4) //this is the one only using my defined types
 */ 
struct FilterSection
{
    Filter HP;
    Filter MID;
    Filter LOP;

    //constructor
    FilterSection()
    {
        HP.order = 2;
        MID.order = 2;
        LOP.order = 4;
    }

    void changeOrder( int order ); // this made no logic sense, so i eddited it a bit
    void bypass();
};

void FilterSection::changeOrder( int order )
{
    LOP.order = order;
    MID.order = order;
    HP.order = order;
    std::cout << "Filter ordered changed to: " << order << std::endl;
}

void FilterSection::bypass()
{
    LOP.bypassLED = true; 
    MID.bypassLED = true; 
    HP.bypassLED = true; 
}
/*
 5)
 */
struct MixerChannel
{
    struct HighPassFilter
    {
        Filter highPass;
        bool isOn;
    };
    int number;
    SendAndReturn sendAndReturn;
    float inputGain = 0;
    float outputGain = 0;
    float pan = 0.5;
    HighPassFilter pad;

    //constructor
    MixerChannel()
    {
        pad.highPass.cutoff = 75.0f; // this is some unnecessary workaround :)
        pad.isOn = false;
    }

    void mute( bool muteButton );
    void solo( bool soloButton, int channelNumber );
};

void MixerChannel::mute(bool muteButton)
{
    if(muteButton)
        outputGain = 0.0f;
    else
        outputGain = 1.0f;

    muteButton = !muteButton;
}
void MixerChannel::solo(bool soloButton, int channelNumber)
{
    number = channelNumber;
    soloButton = !soloButton; 
}
/*
 6)
 */
struct MonoChannel
{
    MixerChannel channel;
    FilterSection filter;
    SendAndReturn sendAndReturn;

    //constructor
    MonoChannel()
    {
        filter.HP.cutoff = 5000.0f;
        filter.MID.cutoff = 800.0f;
        filter.LOP.cutoff = 80.0f;
    }

    void send( MixerChannel destination );
    void mute();
};

void MonoChannel::send( MixerChannel destination )
{
    destination.sendAndReturn.gainLeftChannel = 1.0f;
}
void MonoChannel::mute()
{
    channel.mute(true);
}
/*
 7)
 */
struct StereoChannel
{
    MixerChannel leftChannel;
    MixerChannel rightChannel;
    SendAndReturn sendAndReturn;	

    //constructor
    StereoChannel()
    {
        sendAndReturn.destination = 1;
    }
    
    void send( MixerChannel destination );
    void mute();
};

void StereoChannel::send( MixerChannel destination )
{
    destination.sendAndReturn.gainLeftChannel = 1.0f;
    destination.sendAndReturn.gainRightChannel = 1.0f;
}
void StereoChannel::mute()
{
    leftChannel.mute(true);
    rightChannel.mute(true);
}
/*
 8)
 */
struct OutputChannel
{
    std::string name;
    float gain;

    //constructor
    OutputChannel()
    {
        gain = 0.8f;
        name = "Main Out";
    }

    void setGain( float newGain );
    void sendToHeadphone( MixerChannel headphones );
};

void OutputChannel::setGain( float newGain )
{
    gain = newGain;
}
void OutputChannel::sendToHeadphone( MixerChannel headphones )
{
    headphones.inputGain = 1;
}
/*
 9)
 */
struct Mixer
{
    Mixer( unsigned short numberOfMonoChannels, unsigned short numberOfStereoChannels )
    {
        for(int i = 0; i < numberOfMonoChannels; i++)
        {
            //i don't understand why i cannot create a new instance of MonoChannel like: 
            //monoChannels[i] = new MonoChannel; //help needed
        }

        for(int i = 0; i < numberOfStereoChannels; i++)
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
    OutputChannel mainMix;
    OutputChannel ctrlRoom;

    void boot();
    void sendTestSignal( MixerChannel destinationChannel);
};

void Mixer::boot()
{
    for( int i = 0; i < 4; ++i ) 
    {
        monoChannels[i].channel.outputGain = 1.0f; // i know this is crazy but heck, this mixer has no faders
    }
    for( int i = 0; i < 2; ++i ) 
    {
        stereoChannels[i].leftChannel.outputGain = 1.0f; 
        stereoChannels[i].rightChannel.outputGain = 1.0f;
    }
    mainMix.setGain( 1.0f );
}
void Mixer::sendTestSignal( MixerChannel destinationChannel )
{
    destinationChannel.outputGain = 1;
    //and output is random(noise)
}
/*
10)
*/
struct Wavetable //well, this one is an outlier
{
    std::string name = "blank";

    Wavetable()
    {
        std::cout << "Wavetable is created" << std::endl;
    }

    float getCurrentSample( float waveSamples[] , int currentSampleNr );
    void applyEffect(Effect effect); // 3
};

float Wavetable::getCurrentSample( float waveSamples[], int currentSampleNr )
{
    return waveSamples[currentSampleNr];
}
void  Wavetable::applyEffect( Effect effect )
{
    effect.param1 = rand();
    effect.param2 = rand();
}

#include <iostream>
int main()
{
    Example::main();

    Effect effect1;
    Effect effect2;
    Filter myLOP;
    SendAndReturn SAR_A;
    SendAndReturn SAR_B;
    FilterSection ch_1_Filters;
    MixerChannel subgroup1;
    MonoChannel channel_1;
    MonoChannel channel_2;
    StereoChannel channel_3_4;
    OutputChannel mainMix;
    Mixer alesis(4, 2);
    Wavetable testWavetable;

    effect1.savePreset( 0.3f, 0.4f, 1, effect1.myPresset );
    ch_1_Filters.changeOrder( 4 );

    std::cout << "Default cutoff for the low pass filter is: " << ch_1_Filters.LOP.cutoff << std::endl;
    std::cout << "Pad frequency is: " << subgroup1.pad.highPass.cutoff << ", and the status is " << subgroup1.pad.isOn << std::endl;
    std::cout << "good to go!" << std::endl;
}
