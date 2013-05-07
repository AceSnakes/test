#include "qstring.h"
#include "Defs.h"

QString FindString(const STRING_PAIR pairs[], const QString& key)
{
    int i = 0;
    while (strlen(pairs[i].key) != 0)
    {
        if (key == pairs[i].key)
        {
            return pairs[i].text;
        }
        i++;
    }
    return "";
}

QString GetLoudspeakerName(const LOUDSPEAKERNAME Ls)
{
    if (Ls > LS_FrontWideRight)
        return "";
    return LOUDSPEAKERNAME_LIST[Ls];
}

QString GetEQFrequencyIdentifier(const EQ_FREQUENCY freq)
{
    if (freq > EQ_Wide_Trim)
        return "";
    return EQ_FREQUENCY_LIST[freq];
}

const char* AST1[] = {
    /* 00 */ "ANALOG",
    /* 01 */ "ANALOG",
    /* 02 */ "ANALOG",
    /* 03 */ "PCM",
    /* 04 */ "PCM",
    /* 05 */ "DOLBY DIGITAL",
    /* 06 */ "DTS",
    /* 07 */ "DTS-ES Matrix",
    /* 08 */ "DTS-ES Discrete",
    /* 09 */ "DTS 96/24",
    /* 10 */ "DTS 96/24 ES Matrix",
    /* 11 */ "DTS 96/24 ES Discrete",
    /* 12 */ "MPEG-2 AAC",
    /* 13 */ "WMA9 Pro",
    /* 14 */ "DSD->PCM",
    /* 15 */ "HDMI THROUGH",
    /* 16 */ "DOLBY DIGITAL PLUS",
    /* 17 */ "DOLBY TrueHD",
    /* 18 */ "DTS EXPRESS",
    /* 19 */ "DTS-HD Master Audio",
    /* 20 */ "DTS-HD High Resolution",
    /* 21 */ "DTS-HD High Resolution",
    /* 22 */ "DTS-HD High Resolution",
    /* 23 */ "DTS-HD High Resolution",
    /* 24 */ "DTS-HD High Resolution",
    /* 25 */ "DTS-HD High Resolution",
    /* 26 */ "DTS-HD High Resolution",
    /* 27 */ "DTS-HD Master Audio",
};

const char* AST3[] = {
    /* 00 */ "32kHz",
    /* 01 */ "44.1kHz",
    /* 02 */ "48kHz",
    /* 03 */ "88.2kHz",
    /* 04 */ "96kHz",
    /* 05 */ "176.4kHz",
    /* 06 */ "192kHz",
    /* 06 */ "---",
};

const char* VIDEO_INPUT[] = {
    /* 00 */ "PHONO",
    /* 01 */ "CD",
    /* 02 */ "TUNER",
    /* 03 */ "CD-R/TAPE",
    /* 04 */ "DVD",
    /* 05 */ "TV/SAT",
    /* 06 */ "SAT/CBL",
    /* 07 */ "",
    /* 08 */ "",
    /* 09 */ "",
    /* 10 */ "VIDEO 1",//(VIDEO)",
    /* 11 */ "",
    /* 12 */ "MULTI CH IN",
    /* 13 */ "USB DAC",
    /* 14 */ "VIDEO 2",
    /* 15 */ "DVR/BDR",
    /* 16 */ "",
    /* 17 */ "iPod/USB",
    /* 18 */ "XM RADIO",
    /* 19 */ "HDMI 1",
    /* 20 */ "HDMI 2",
    /* 21 */ "HDMI 3",
    /* 22 */ "HDMI 4",
    /* 23 */ "HDMI 5",
    /* 24 */ "HDMI 6",
    /* 25 */ "BD",
    /* 26 */ "HOME MEDIA GALLERY(Internet Radio)",
    /* 27 */ "SIRIUS",
    /* 28 */ "",
    /* 29 */ "",
    /* 30 */ "",
    /* 31 */ "HDMI (cyclic)",
    /* 32 */ "",
    /* 33 */ "ADAPTER PORT",
    /* 34 */ "HDMI 7",
    /* 35 */ "",
    /* 36 */ "",
    /* 37 */ "",
    /* 38 */ "INTERNET RADIO",
    /* 39 */ "",
    /* 40 */ "SiriusXM",
    /* 41 */ "PANDORA",
    /* 42 */ "",
    /* 43 */ "",
    /* 44 */ "MEDIA SERVER",
    /* 45 */ "FAVORITES",
    /* 46 */ "",
    /* 47 */ "",
    /* 48 */ "MHL",
};


const char* VIDEO_INPUT_TERMINAL[] = {
    /* 00 */ "---",
    /* 01 */ "VIDEO",
    /* 02 */ "S-VIDEO",
    /* 03 */ "COMPONENT",
    /* 04 */ "HDMI",
    /* 05 */ "Self OSD/JPEG",
};

const char* VIDEO_INPUT_RESOLUTION[] = {
    /* 00 */ "---",
    /* 01 */ "480/60i",
    /* 02 */ "576/50i",
    /* 03 */ "480/60p",
    /* 04 */ "576/50p",
    /* 05 */ "720/60p",
    /* 06 */ "720/50p",
    /* 07 */ "1080/60i",
    /* 08 */ "1080/50i",
    /* 09 */ "1080/60p",
    /* 10 */ "1080/50p",
    /* 11 */ "1080/24p",
};

const char* VIDEO_INPUT_ASPECT[] = {
    /* 00 */ "---",
    /* 01 */ "4:3",
    /* 02 */ "16:9",
    /* 03 */ "14:9",
};

const char* VIDEO_INPUT_COLOR_FORMAT[] = {
    /* 00 */ "---",
    /* 01 */ "RGB Limit",
    /* 02 */ "RGB Full",
    /* 03 */ "YcbCr444",
    /* 04 */ "YcbCr422",
};

const char* VIDEO_INPUT_BITS[] = {
    /* 00 */ "---",
    /* 01 */ "24bit (8bit*3)",
    /* 02 */ "30bit (10bit*3)",
    /* 03 */ "36bit (12bit*3)",
    /* 04 */ "48bit (16bit*3)",
};

const char* VIDEO_INPUT_COLOR_SPACE[] = {
    /* 00 */ "---",
    /* 01 */ "Standard",
    /* 02 */ "xvYCC601",
    /* 03 */ "xvYCC709",
    /* 04 */ "sYCC",
    /* 05 */ "AdobeYCC601",
    /* 06 */ "AdobeRGB",
};

const STRING_PAIR LISTENING_MODE[]  = {
    {"0001", "STEREO (cyclic)"},
    {"0005", "AUTO SURR/STREAM DIRECT (cyclic)"},
    {"0006", "AUTO SURROUND"},
    {"0151", "Auto Level Control (A.L.C.)"},
    {"0007", "DIRECT"},
    {"0008", "PURE DIRECT"},
    {"0009", "STEREO (direct set)"},
    {"0003", "Front Stage Surround Advance Focus"},
    {"0004", "Front Stage Surround Advance Wide"},
    {"0153", "RETRIEVER AIR"},
    {"0010", "STANDARD"},
    {"0011", "(2ch source)"},
    {"0013", "PRO LOGIC2 MOVIE"},
    {"0018", "PRO LOGIC2x MOVIE"},
    {"0014", "PRO LOGIC2 MUSIC"},
    {"0019", "PRO LOGIC2x MUSIC"},
    {"0015", "PRO LOGIC2 GAME"},
    {"0020", "PRO LOGIC2x GAME"},
    {"0031", "PRO LOGIC2z Height"},
    {"0032", "WIDE SURROUND MOVIE"},
    {"0033", "WIDE SURROUND MUSIC"},
    {"0012", "PRO LOGIC"},
    {"0016", "Neo:6 CINEMA"},
    {"0017", "Neo:6 MUSIC"},
    {"0028", "XM HD SURROUND"},
    {"0029", "NEURAL SURROUND"},
    {"0021", "(Multi ch source)"},
    {"0022", "(Multi ch source)+DOLBY EX"},
    {"0023", "(Multi ch source)+PRO LOGIC2x MOVIE"},
    {"0024", "(Multi ch source)+PRO LOGIC2x MUSIC"},
    {"0034", "(Multi-ch Source)+PRO LOGIC2z HEIGHT"},
    {"0035", "(Multi-ch Source)+WIDE SURROUND MOVIE"},
    {"0036", "(Multi-ch Source)+WIDE SURROUND MUSIC"},
    {"0025", "DTS-ES Neo:6"},
    {"0026", "DTS-ES matrix"},
    {"0027", "DTS-ES discrete"},
    {"0030", "DTS-ES 8ch discrete"},
    {"0100", "ADVANCED SURROUND (cyclic)"},
    {"0101", "ACTION"},
    {"0103", "DRAMA"},
    {"0102", "SCI-FI"},
    {"0105", "MONO FILM"},
    {"0104", "ENTERTAINMENT SHOW"},
    {"0106", "EXPANDED THEATER"},
    {"0116", "TV SURROUND"},
    {"0118", "ADVANCED GAME"},
    {"0117", "SPORTS"},
    {"0107", "CLASSICAL"},
    {"0110", "ROCK/POP"},
    {"0109", "UNPLUGGED"},
    {"0112", "EXTENDED STEREO"},
    {"0113", "PHONES SURROUND"},
    {"0050", "THX (cyclic)"},
    {"0051", "PROLOGIC + THX CINEMA"},
    {"0052", "PL2 MOVIE + THX CINEMA"},
    {"0053", "Neo:6 CINEMA + THX CINEMA"},
    {"0054", "PL2x MOVIE + THX CINEMA"},
    {"0092", "PL2z HEIGHT + THX CINEMA"},
    {"0055", "THX SELECT2 GAMES"},
    {"0068", "THX CINEMA (for 2ch)"},
    {"0069", "THX MUSIC (for 2ch)"},
    {"0070", "THX GAMES (for 2ch)"},
    {"0071", "PL2 MUSIC + THX MUSIC"},
    {"0072", "PL2x MUSIC + THX MUSIC"},
    {"0093", "PL2z HEIGHT + THX MUSIC"},
    {"0073", "Neo:6 MUSIC + THX MUSIC"},
    {"0074", "PL2 GAME + THX GAMES"},
    {"0075", "PL2x GAME + THX GAMES"},
    {"0094", "PL2z HEIGHT + THX GAMES"},
    {"0076", "THX ULTRA2 GAMES"},
    {"0077", "PROLOGIC + THX MUSIC"},
    {"0078", "PROLOGIC + THX GAMES"},
    {"0056", "THX CINEMA (for multi ch)"},
    {"0057", "THX SURROUND EX (for multi ch)"},
    {"0058", "PL2x MOVIE + THX CINEMA (for multi ch)"},
    {"0095", "PL2z HEIGHT + THX CINEMA (for multi ch)"},
    {"0059", "ES Neo:6 + THX CINEMA (for multi ch)"},
    {"0060", "ES MATRIX + THX CINEMA (for multi ch)"},
    {"0061", "ES DISCRETE + THX CINEMA (for multi ch)"},
    {"0067", "ES 8ch DISCRETE + THX CINEMA (for multi ch)"},
    {"0062", "THX SELECT2 CINEMA (for multi ch)"},
    {"0063", "THX SELECT2 MUSIC (for multi ch)"},
    {"0064", "THX SELECT2 GAMES (for multi ch)"},
    {"0065", "THX ULTRA2 CINEMA (for multi ch)"},
    {"0066", "THX ULTRA2 MUSIC (for multi ch)"},
    {"0079", "THX ULTRA2 GAMES (for multi ch)"},
    {"0080", "THX MUSIC (for multi ch)"},
    {"0081", "THX GAMES (for multi ch)"},
    {"0082", "PL2x MUSIC + THX MUSIC (for multi ch)"},
    {"0096", "PL2z HEIGHT + THX MUSIC (for multi ch)"},
    {"0083", "EX + THX GAMES (for multi ch)"},
    {"0097", "PL2z HEIGHT + THX GAMES (for multi ch)"},
    {"0084", "Neo:6 + THX MUSIC (for multi ch)"},
    {"0085", "Neo:6 + THX GAMES (for multi ch)"},
    {"0086", "ES MATRIX + THX MUSIC (for multi ch)"},
    {"0087", "ES MATRIX + THX GAMES (for multi ch)"},
    {"0088", "ES DISCRETE + THX MUSIC (for multi ch)"},
    {"0089", "ES DISCRETE + THX GAMES (for multi ch)"},
    {"0090", "ES 8CH DISCRETE + THX MUSIC (for multi ch)"},
    {"0091", "ES 8CH DISCRETE + THX GAMES (for multi ch)"},
    {"0152", "OPTIMUM SURROUND"},
    {"", ""},
};


const STRING_PAIR PLAYING_LISTENING_MODE[]  = {
    {"0001", "STEREO"},
    {"0002", "F.S.SURR FOCUS"},
    {"0003", "F.S.SURR WIDE"},
    {"0004", "RETRIEVER AIR"},
    {"0101", "[)(]PLIIx MOVIE"},
    {"0102", "[)(]PLII MOVIE"},
    {"0103", "[)(]PLIIx MUSIC"},
    {"0104", "[)(]PLII MUSIC"},
    {"0105", "[)(]PLIIx GAME"},
    {"0106", "[)(]PLII GAME"},
    {"0107", "[)(]PROLOGIC"},
    {"0108", "Neo:6 CINEMA"},
    {"0109", "Neo:6 MUSIC"},
    {"010a", "XM HD Surround"},
    {"010b", "NEURAL SURR"},
    {"010c", "2ch Straight Decode"},
    {"010d", "[)(]PLIIz HEIGHT"},
    {"010e", "WIDE SURR MOVIE"},
    {"010f", "WIDE SURR MUSIC"},
    {"1101", "[)(]PLIIx MOVIE"},
    {"1102", "[)(]PLIIx MUSIC"},
    {"1103", "[)(]DIGITAL EX"},
    {"1104", "DTS +Neo:6 / DTS-HD +Neo:6"},
    {"1105", "ES MATRIX"},
    {"1106", "ES DISCRETE"},
    {"1107", "DTS-ES 7.1"},
    {"1108", "multi ch Straight Decode"},
    {"1109", "[)(]PLIIz HEIGHT"},
    {"110a", "WIDE SURR MOVIE"},
    {"110b", "WIDE SURR MUSIC"},
    {"0201", "ACTION"},
    {"0202", "DRAMA"},
    {"0203", "SCI-FI"},
    {"0204", "MONOFILM"},
    {"0205", "ENT.SHOW"},
    {"0206", "EXPANDED"},
    {"0207", "TV SURROUND"},
    {"0208", "ADVANCEDGAME"},
    {"0209", "SPORTS"},
    {"020a", "CLASSICAL"},
    {"020b", "ROCK/POP"},
    {"020c", "UNPLUGGED"},
    {"020d", "EXT.STEREO"},
    {"020e", "PHONES SURR."},
    {"0301", "[)(]PLIIx MOVIE +THX"},
    {"0302", "[)(]PLII MOVIE +THX"},
    {"0303", "[)(]PL +THX CINEMA"},
    {"0304", "Neo:6 CINEMA +THX"},
    {"0305", "THX CINEMA"},
    {"0306", "[)(]PLIIx MUSIC +THX"},
    {"0307", "[)(]PLII MUSIC +THX"},
    {"0308", "[)(]PL +THX MUSIC"},
    {"0309", "Neo:6 MUSIC +THX"},
    {"030a", "THX MUSIC"},
    {"030b", "[)(]PLIIx GAME +THX"},
    {"030c", "[)(]PLII GAME +THX"},
    {"030d", "[)(]PL +THX GAMES"},
    {"030e", "THX ULTRA2 GAMES"},
    {"030f", "THX SELECT2 GAMES"},
    {"0310", "THX GAMES"},
    {"0311", "[)(]PLIIz +THX CINEMA"},
    {"0312", "[)(]PLIIz +THX MUSIC"},
    {"0313", "[)(]PLIIz +THX GAMES"},
    {"1301", "THX Surr EX"},
    {"1302", "Neo:6 +THX CINEMA"},
    {"1303", "ES MTRX +THX CINEMA"},
    {"1304", "ES DISC +THX CINEMA"},
    {"1305", "ES7.1 +THX CINEMA"},
    {"1306", "[)(]PLIIx MOVIE +THX"},
    {"1307", "THX ULTRA2 CINEMA"},
    {"1308", "THX SELECT2 CINEMA"},
    {"1309", "THX CINEMA"},
    {"130a", "Neo:6 +THX MUSIC"},
    {"130b", "ES MTRX +THX MUSIC"},
    {"130c", "ES DISC +THX MUSIC"},
    {"130d", "ES7.1 +THX MUSIC"},
    {"130e", "[)(]PLIIx MUSIC +THX"},
    {"130f", "THX ULTRA2 MUSIC"},
    {"1310", "THX SELECT2 MUSIC"},
    {"1311", "THX MUSIC"},
    {"1312", "Neo:6 +THX GAMES"},
    {"1313", "ES MTRX +THX GAMES"},
    {"1314", "ES DISC +THX GAMES"},
    {"1315", "ES7.1 +THX GAMES"},
    {"1316", "[)(]EX +THX GAMES"},
    {"1317", "THX ULTRA2 GAMES"},
    {"1318", "THX SELECT2 GAMES"},
    {"1319", "THX GAMES"},
    {"131a", "[)(]PLIIz +THX CINEMA"},
    {"131b", "[)(]PLIIz +THX MUSIC"},
    {"131c", "[)(]PLIIz +THX GAMES"},
    {"0401", "STEREO"},
    {"0402", "[)(]PLII MOVIE"},
    {"0403", "[)(]PLIIx MOVIE"},
    {"0404", "Neo:6 CINEMA"},
    {"0405", "AUTO SURROUND Straight Decode"},
    {"0406", "[)(]DIGITAL EX"},
    {"0407", "[)(]PLIIx MOVIE"},
    {"0408", "DTS +Neo:6"},
    {"0409", "ES MATRIX"},
    {"040a", "ES DISCRETE"},
    {"040b", "DTS-ES 7.1"},
    {"040c", "XM HD Surround"},
    {"040d", "NEURALSURR"},
    {"040e", "RETRIEVER AIR"},
    {"0501", "STEREO"},
    {"0502", "[)(]PLII MOVIE"},
    {"0503", "[)(]PLIIx MOVIE"},
    {"0504", "Neo:6 CINEMA"},
    {"0505", "ALC Straight Decode"},
    {"0506", "[)(]DIGITAL EX"},
    {"0507", "[)(]PLIIx MOVIE"},
    {"0508", "DTS +Neo:6"},
    {"0509", "ES MATRIX"},
    {"050a", "ES DISCRETE"},
    {"050b", "DTS-ES 7.1"},
    {"050c", "XM HD Surround"},
    {"050d", "NEURAL SURR"},
    {"050e", "RETRIEVER AIR"},
    {"0601", "STEREO"},
    {"0602", "[)(]PLII MOVIE"},
    {"0603", "[)(]PLIIx MOVIE"},
    {"0604", "Neo:6 CINEMA"},
    {"0605", "STREAM DIRECT NORMAL Straight Decode"},
    {"0606", "[)(]DIGITAL EX"},
    {"0607", "[)(]PLIIx MOVIE"},
    {"0608", "(nothing)"},
    {"0609", "ES MATRIX"},
    {"060a", "ES DISCRETE"},
    {"060b", "DTS-ES 7.1"},
    {"0701", "STREAM DIRECT PURE 2ch"},
    {"0702", "[)(]PLII MOVIE"},
    {"0703", "[)(]PLIIx MOVIE"},
    {"0704", "Neo:6 CINEMA"},
    {"0705", "STREAM DIRECT PURE Straight Decode"},
    {"0706", "[)(]DIGITAL EX"},
    {"0707", "[)(]PLIIx MOVIE"},
    {"0708", "(nothing)"},
    {"0709", "ES MATRIX"},
    {"070a", "ES DISCRETE"},
    {"070b", "DTS-ES 7.1"},
    {"0881", "OPTIMUM"},
    {"0e01", "HDMI THROUGH"},
    {"0f01", "MULTI CH IN"},
    {"", ""},
};

const char* LOUDSPEAKERNAME_LIST[] = {
    "L__", //Front Left
    "R__", //Front Right
    "C__", //Center
    "SL_", //Surround Left
    "SR_", //Surround Right
    "SBL", //Surround Back Left
    "SBR", //Surround Back Right
    "LH_", //Front Height Left
    "RH_", //Front Height Right
    "LW_", //Front Wide Left
    "RW_", //Front Wide Right
};

const char* EQ_FREQUENCY_LIST[] = {
    "00", //63Hz
    "01", //125Hz
    "02", //250Hz
    "03", //500Hz
    "04", //1kHz
    "05", //2kHz
    "06", //4kHz
    "07", //8kHz
    "08", //16kHz
    "09", //EQ Wide Trim
};
