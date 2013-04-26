#ifndef DEFS_H
#define DEFS_H


struct STRING_PAIR
{
    const char *key;
    const char *text;
};

QString FindString(const STRING_PAIR pairs[], const QString& key);

enum MCACCMEMORY
{
    MCACCMemoryCurrent = 0,
    MCACCMemory1 = 1,
    MCACCMemory2 = 2,
    MCACCMemory3 = 3,
    MCACCMemory4 = 4,
    MCACCMemory5 = 5
};

enum LOUDSPEAKERNAME
{
    LS_FrontLeft,
    LS_FrontRight,
    LS_Center,
    LS_SurroundLeft,
    LS_SurroundRight,
    LS_SurroundBackLeft,
    LS_SurroundBackRight,
    LS_FrontHeightLeft,
    LS_FrontHeightRight,
    LS_FrontWideLeft,
    LS_FrontWideRight
};

enum EQ_FREQUENCY
{
    EQ_63Hz,
    EQ_125Hz,
    EQ_250Hz,
    EQ_500Hz,
    EQ_1kHz,
    EQ_2kHz,
    EQ_4kHz,
    EQ_8kHz,
    EQ_16kHz,
    EQ_Wide_Trim
};

QString GetLoudspeakerName(const LOUDSPEAKERNAME Ls);
QString GetEQFrequencyIdentifier(const EQ_FREQUENCY freq);

extern const char* AST1[];
extern const char* AST3[];
extern const char* VIDEO_INPUT[];
extern const char* VIDEO_INPUT_TERMINAL[];
extern const char* VIDEO_INPUT_RESOLUTION[];
extern const char* VIDEO_INPUT_ASPECT[];
extern const char* VIDEO_INPUT_COLOR_FORMAT[];
extern const char* VIDEO_INPUT_BITS[];
extern const char* VIDEO_INPUT_COLOR_SPACE[];
extern const STRING_PAIR LISTENING_MODE[];
extern const STRING_PAIR PLAYING_LISTENING_MODE[];
extern const char* LOUDSPEAKERNAME_LIST[];
extern const char* EQ_FREQUENCY_LIST[];
//extern const STRING_PAIR SET_PLAYING_LISTENING_MODE[];

#endif // DEFS_H
