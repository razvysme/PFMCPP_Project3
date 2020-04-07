/*
 Project 3 - Part 5 / 5
 video: Chapter 2 - Part 10
 Scope and Lifetime tasks
 
Create a branch named Part5

 video covered:
    variable scope and lifetime relative to { }
    while loops
    for loops()
 
 tasks
 
 1) add some new member functions to your types. 
 
 2) use while() or for() loops to do something interesting inside these new member functions.
         a) for example: have a loop that modifies a member variable of some object created outside the loop.
         b) when that member variable reaches a certain threshold, return it mid-loop.
         c) maybe use function parameters to control the starting value of that member variable or control the threshold
         
 3) call those new member functions in main()
 
 4) use std::cout statements to print out information about what your loops did.
 
 5) click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 
 example:
 */

#include <iostream>
namespace Example {
struct Bar 
{ 
    int num = 0; 
    Bar(int n) : num(n) { } 
};
struct Foo
{
    Bar scopeLifetimeFunc( int threshold, int startingVal ) //3), 4c) 
    {
        Bar bar(startingVal);                //4a)
        while( bar.num < threshold )         //4a) 
        { 
            bar.num += 1;                    //4a)
            
            if( bar.num >= threshold )       //4b)
                return bar;
        }
        
        return Bar {-1}; //if your startingValue >= threshold, the while loop never runs
    }
};

int main()
{
    Foo foo;
    auto bar = foo.scopeLifetimeFunc(3, 1);        //5) 
    
    std::cout << "bar.num: " << bar.num << std::endl;     //6) 
    return 0;
}
}

//call Example::main() in main()



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
            param1 = 0;
            param2 = 0;
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
        number = 1;
    }

    void savePreset( float currentParam1, float currentParam2, float effectNumber, Preset presetName);
    void changePreset( float currentParam1, float currentParam2 );
    void ressetPresets(Effect effect);
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
    std::cout << "Effect number changed to: " << number++ << std::endl;
}
void Effect::ressetPresets(Effect effect)
{   
    unsigned short currentEffectNr = effect.number;
    while( currentEffectNr < 10)
    {
        param1=0;
        param2=0;
        std::cout << "Effect number: " << currentEffectNr << " is reseted." <<std::endl;
        currentEffectNr++;        
    }
}
/*
 2)
 */
struct Filter
{
    std::string type;
    int order;
    bool bypassLED = false;
    float cutoff = 10000;

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
    void changeCutoff( float );
};

std::string Filter::changeType( std::string currentType )
{
    std::cout << "Cutoff is: " << cutoff << std::endl;
    return currentType;
}

void Filter::bypass()
{
    //well this is kinda hard to implement without the audio stream, but it would look something like y[n]=x[n], therefore i added the bypassLED bool so this declaration is not empty.
    bypassLED = true;
}

void Filter::changeCutoff(float newCutoff)
{
    if ( newCutoff < cutoff )
    {
        while ( newCutoff < cutoff )
        {
            cutoff -= 100;
            std::cout << "Cutoff decreaded by 100" << std::endl;
        }
    }
    else if( newCutoff * 0.99f < cutoff  && newCutoff * 1.01f > cutoff )  //hacky way of checking for floats equality
    {
        std::cout << "Cutoff not changed." << std::endl;    
    }
    else
    {
        while ( cutoff < newCutoff )
        {
            cutoff += 100;
            std::cout << "Cutoff increaded by 100" << std::endl;
        }
    }   
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

    float fadeIn( float endGain )
    {
        while( gainLeftChannel < endGain )
        {
            std::cout <<  "Fade volume " << gainLeftChannel << std::endl;
            
            gainLeftChannel+= 0.1f;
        }
        return gainLeftChannel;
    }
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
    Filter increaseFilter ( int stabilityTreshold, int startingValue ) 
    {
        Filter localFilter;
        for ( int i = startingValue; i<stabilityTreshold; i++ )
        {
            localFilter.order = i;
            if ( localFilter.order == stabilityTreshold)
                return localFilter;
        }
        return localFilter;
    }
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
        bool isOn = false;
    };
    
    int number = 1;
    SendAndReturn sendAndReturn;
    float inputGain = 0.7f;
    float outputGain = 0.7f;
    float pan = 0.5f;
    HighPassFilter pad;

    //constructor
    MixerChannel()
    {
        pad.highPass.cutoff = 75.0f; // this is some unnecessary workaround :)
        pad.isOn = false;
        
    }

    void mute( bool muteButton );
    void solo( bool soloButton, int channelNumber );
    void turnOffPad(HighPassFilter localPad)
    {   
        if (localPad.isOn)
        {
            while ( localPad.highPass.cutoff  > 0.0f )
                localPad.highPass.cutoff -= 1.0f;
        }
    }


};

void MixerChannel::mute(bool muteButton)
{
    if(muteButton)
        outputGain = 0.0f;
    else
        outputGain = 1.0f;

    muteButton = !muteButton;
    std::cout << "Mixer channel number: " << number << " is muted." << std::endl;
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
    float panLeft( MixerChannel channel );

};

void MonoChannel::send( MixerChannel destination )
{
    destination.sendAndReturn.gainLeftChannel = 1.0f;
}
void MonoChannel::mute()
{
    channel.mute(true);
}
float MonoChannel::panLeft( MixerChannel localChannel )
{
        {
        for ( float i = channel.pan; i > 0.0f  && i < 0.5f; i -= 0.05f )
        {
            localChannel.pan = i;
            std::cout << localChannel.pan << std::endl;
        }
        return localChannel.pan;
    }
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
    void panRight()
    {
        while (leftChannel.outputGain > 0 )
        {
            leftChannel.outputGain -= 0.1f;
            rightChannel.outputGain = 1.0f - leftChannel.outputGain;
            std::cout << "LC pan = " << leftChannel.outputGain << ", RC pan = " << rightChannel.outputGain << std::endl;
        }
    }
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
    for (int i = 0; i < 10; i++)
    {
        if( gain < newGain)
        {
            gain += newGain * 1/10;
            std::cout << "new gain is: " << gain << std::endl;
        }
        else
        {
            gain -= newGain * 1/10;
            std::cout << "new gain is: " << gain << std::endl; 
        }

    }
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
            std::cout << "New Mono Channel Created" << std::endl;
        }

        for(int i = 0; i < numberOfStereoChannels; i++)
        {
            std::cout << "New stereo Channel Created" << std::endl;
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
    float wavetable[64];
    Wavetable()
    {
        std::cout << "Wavetable is created" << std::endl;
    }

    float getCurrentSample( float waveSamples[] , int currentSampleNr );
    void applyEffect(Effect effect); // 3
    void populateWavetable(Wavetable destination);
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
void Wavetable::populateWavetable( Wavetable destination )
{
    for( int i = 0; i < 64; i++ )
    {
        destination.wavetable[i] = rand();
        std::cout << "Wavetable position " << i << " is " << wavetable[i] <<std::endl;
    }
}


#include <iostream>
int main()
{
    Example::main();

    Effect effect1;
    Effect effect2;
    Filter myLOP;
    SendAndReturn sendAndReturn_A;
    SendAndReturn sendAndReturn_B;
    FilterSection ch_1_Filters;
    MixerChannel subgroup1;
    MonoChannel channel_1;
    MonoChannel channel_2;
    StereoChannel channel_3_4;
    OutputChannel mainMix;
    Mixer alesis(4, 2);
    Wavetable testWavetable;

    effect1.savePreset( 0.3f, 0.4f, 1, effect1.myPresset );
    effect1.changePreset(0.2f, 1.0f);
    ch_1_Filters.changeOrder( 4 );
    channel_1.mute();
    effect1.ressetPresets(effect1);
    myLOP.changeCutoff(10000);
    sendAndReturn_A.gainLeftChannel = sendAndReturn_A.fadeIn( 0.8f );
    testWavetable.populateWavetable(testWavetable);
    channel_3_4.panRight();
    mainMix.setGain(0.3f);

    std::cout << "Default cutoff for the low pass filter is: " << ch_1_Filters.LOP.cutoff << std::endl;
    std::cout << "Pad frequency is: " << subgroup1.pad.highPass.cutoff << ", and the status is " << subgroup1.pad.isOn << std::endl;
    std::cout << "good to go!" << std::endl;
}
