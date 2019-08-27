#include "../def_pix_tests.h"
#include "../uniformity_tests.h"
#include "../sharpness_tests.h"
#include "../visual_tests.h"
#include "../response_time_tests.h"

#pragma once

ProductTestRoutine edgeTestRoutine
{
    response_time_test,
    def_px_test_white, 
    def_px_test_black,
    def_px_test_red,
    def_px_test_green,
    def_px_test_blue,
    uniformity_test_75_percent,
    uniformity_test_50_percent,
    uniformity_test_25_percent,
    sharpness_test_10px_font,
    sharpness_test_12px_font,
    sharpness_test_14px_font,
    sharpness_test_16px_font,
    visual_test_no_border,
    visual_test_no_border_grayscale,
    visual_test_black_border,
    visual_test_white_border,
    visual_test_red_border,
    visual_test_green_border,
    visual_test_blue_border
};
