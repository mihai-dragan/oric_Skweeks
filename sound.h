#define AY_AChanelL 0
#define AY_AChanelH 1
#define AY_BChanelL 2
#define AY_BChanelH 3
#define AY_CChanelL 4
#define AY_CChanelH 5
#define AY_Noise 6
#define AY_Mixer 7
#define AY_AmplitudeA 8
#define AY_AmplitudeB 9
#define AY_AmplitudeC 10
#define AY_EnvelopeL 11
#define AY_EnvelopeH 12
#define AY_Envelope 13

#define TONE	0
#define NOISE	1
#define MIXER	2
#define VOLUME	3
#define ENVPER	4
#define ENVTYP	5
#define TIME	6

#define TONENOISE	0
#define JUSTNOISE	1
#define JUSTTONE	2
#define NONE		3

struct instrument {
	unsigned int tonef;
	byte noisep;
	byte mixcontrol;
	byte volume;
	unsigned int envelopep;
	byte envelopet;
	byte snd_time;
};

struct instrument instruments[2];

byte mixer = 127;
byte playtime = 0;

void w8912(byte reg, byte val) {
    __asm__("ldy #0");
    __asm__("lda (sp),y");
    __asm__("tax");
    __asm__("iny");
    __asm__("lda (sp),y");
    __asm__("jsr $F590");
}

byte play_chanA(unsigned int period) {
    if(playtime == 1) {
		if(instruments[0].tonef<4096) {
			w8912(AY_AChanelL, instruments[0].tonef % 256);
			w8912(AY_AChanelH, instruments[0].tonef / 256);
		} else {
			w8912(AY_AChanelL, period % 256);
			w8912(AY_AChanelH, period / 256);
		}
		w8912(AY_Noise, instruments[0].noisep);
        if (instruments[0].mixcontrol == JUSTTONE) mixer &= 254;
        if (instruments[0].mixcontrol == JUSTNOISE) mixer &= 247;
        if (instruments[0].mixcontrol == TONENOISE) { mixer &= 247; mixer &= 254; }
        w8912(AY_Mixer, mixer);
        w8912(AY_AmplitudeA, instruments[0].volume);
        w8912(AY_EnvelopeL, instruments[0].envelopep % 256);
        w8912(AY_EnvelopeH, instruments[0].envelopep / 256);
        w8912(AY_Envelope, instruments[0].envelopet);
        return 1;
    } else {
		if(playtime >= instruments[0].snd_time) {
			playtime = 0;
			playing = 0;
			w8912(AY_Mixer, mixer|9);
			w8912(AY_AmplitudeA, 0);
			w8912(AY_Envelope, 0);
			return 0;
		}
		return 1;
	}
}

byte play_chanB(unsigned int period) {
    if(playtime == 1) {
		if(instruments[1].tonef<4096) {
			w8912(AY_BChanelL, instruments[1].tonef % 256);
			w8912(AY_BChanelH, instruments[1].tonef / 256);
		} else {
			w8912(AY_BChanelL, period % 256);
			w8912(AY_BChanelH, period / 256);
		}
		w8912(AY_Noise, instruments[1].noisep);
        if (instruments[1].mixcontrol == JUSTTONE) mixer &= 125;
        if (instruments[1].mixcontrol == JUSTNOISE) mixer &= 111;
        if (instruments[1].mixcontrol == TONENOISE) { mixer &= 125; mixer &= 111; }
        w8912(AY_Mixer, mixer);
        w8912(AY_AmplitudeB, instruments[1].volume);
        w8912(AY_EnvelopeL, instruments[1].envelopep % 256);
        w8912(AY_EnvelopeH, instruments[1].envelopep / 256);
        w8912(AY_Envelope, instruments[1].envelopet);
        return 1;
    } else {
		if(playtime >= instruments[1].snd_time) {
			playtime = 0;
			playing = 0;
			w8912(AY_Mixer, mixer|18);
			w8912(AY_AmplitudeB, 0);
			w8912(AY_Envelope, 0);
			return 0;
		}
		return 1;
	}
}

void stop_sound() {
	playtime = 0;
	playing = 0;
	mixer = 127;
	w8912(AY_Mixer, 127);
	w8912(AY_AmplitudeA, 0);
	w8912(AY_AmplitudeB, 0);
	w8912(AY_Envelope, 0);
}

byte load_instrA(byte *instr) {
	if(instr[2] > 127) instruments[0].volume = 16;
	else instruments[0].volume = instr[1] >> 4;
	instruments[0].mixcontrol = ((byte)(instr[2] << 1)) >> 6;
	instruments[0].tonef = instr[1] << 4;
	instruments[0].tonef = (instruments[0].tonef << 4) + instr[0];
	instruments[0].noisep = ((byte)(instr[2] << 3)) >> 3;
	
	if(instruments[0].volume == 16) {
		instruments[0].envelopep = (instr[4] << 8) + instr[3];
		instruments[0].envelopet = instr[5];
		instruments[0].snd_time = instr[6];
		return 7;
	} else {
		instruments[0].snd_time = instr[3];
		return 4;
	}
}

byte load_instrB(byte *instr) {
	if(instr[2] > 127) instruments[1].volume = 16;
	else instruments[1].volume = instr[1] >> 4;
	instruments[1].mixcontrol = ((byte)(instr[2] << 1)) >> 6;
	instruments[1].tonef = instr[1] << 4;
	instruments[1].tonef = (instruments[1].tonef << 4) + instr[0];
	instruments[1].noisep = ((byte)(instr[2] << 3)) >> 3;
	
	if(instruments[1].volume == 16) {
		instruments[1].envelopep = (instr[4] << 8) + instr[3];
		instruments[1].envelopet = instr[5];
		instruments[1].snd_time = instr[6];
		return 7;
	} else {
		instruments[1].snd_time = instr[3];
		return 4;
	}
}

void play_effect(byte *name, unsigned int freq) {
	stop_sound();
	load_instrA(name);
	playtime = 1;
	play_chanA(freq);
	playtime=2; playing=1;
}
