/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#ifndef BINARYDATA_H_50825276_INCLUDED
#define BINARYDATA_H_50825276_INCLUDED

namespace BinaryData
{
    extern const char*   delay_png;
    const int            delay_pngSize = 9114;

    extern const char*   echo_png;
    const int            echo_pngSize = 10791;

    extern const char*   play_png;
    const int            play_pngSize = 11150;

    extern const char*   radar_jpg;
    const int            radar_jpgSize = 34714;

    extern const char*   radar_png;
    const int            radar_pngSize = 9962;

    extern const char*   samp1_png;
    const int            samp1_pngSize = 10502;

    extern const char*   sine_jpg;
    const int            sine_jpgSize = 22784;

    extern const char*   sine_png;
    const int            sine_pngSize = 78927;

    extern const char*   Test0_png;
    const int            Test0_pngSize = 10169;

    extern const char*   Test1_png;
    const int            Test1_pngSize = 4013;

    extern const char*   Test2_png;
    const int            Test2_pngSize = 5349;

    extern const char*   trem_png;
    const int            trem_pngSize = 66344;

    extern const char*   vib_jpg;
    const int            vib_jpgSize = 22530;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 13;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

#endif
