/*
 *                    GNU GENERAL PUBLIC LICENSE
 *                       Version 3, 29 June 2007
 *
 * Copyright (C) 2007 Free Software Foundation, Inc. <http://fsf.org/>
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
 *
 * Written by Leonardo Maccari Rufino
 */

#include "sdp_field_test.h"
#include <iostream>

//-------------------------------------------

int main()
{
    std::cout << "SDP test initialized\n";

    if (!SDP_Field_Test::init())
    {
        std::cout << "SDP field test FAILED!\n";
        return 1;
    }

    std::cout << "SDP test completed successfully\n";
    return 0;
}

//-------------------------------------------
