/**
 * @file ChessColorDetection.h
 * @author Ines Rohrbach, Nico Schramm
 * @brief Helper class for VEML6040 color sensor.
 * @version 0.1
 * @date 2024-10-30
 * 
 * @copyright Copyright (c) 2024
*/

#ifndef ChessColorDetection_h
#define ChessColorDetection_h

#include <algorithm>
#include <veml6040.h>

enum RGBWColor {
    RGBW_RED,
    RGBW_GREEN,
    RGBW_BLUE,
    RGBW_WHITE
};

class ChessColorDetection {
protected:
    VEML6040 rgbwSensor;

    // constants
    const double IS_WHITE_FIELD_THRESHOLD = 100.0;
    const double MAX_NORMALIZED_COLOR_VALUE = 255.0;
    const double MAX_RAW_AMBIENT_VALUE = 2061.0;
    const double MAX_RGBW_SENSOR_VALUE = 65535.0;
    
public:
    /**
     * @brief Initialize VEML6040 color sensor and begin transmission
     * 
     * @return true if sensor was started successfully
     * @return false if sensor could not be started
     */
    bool begin();

    /**
     * @brief Get normalized value of ambient light sensor on a scale from 0 to 255.
     * 
     * @return double normalized value
     */
    double getNormalizedAmbientValue();

    /**
     * @brief Get raw color value of RGBW sensor (**not** normalized!).
     *
     * Raw value is scaled on 16 bits.
     * For normalized value see \p getNormalizedColorValue.
     * 
     * @param color color which to get
     * @return double color value
     */
    double getRawColorValue(RGBWColor color);

    /**
     * @brief Get the normalized value of color sensor on a scale of 0 to 255 based
     *        on ambient lighting conditions.
     *
     * For \p ambientLightValue please use \p getNormalizedColorValue.
     * 
     * @param color color which to get value for
     * @param ambientLightValue **normalized** value of ambient light sensor
     * @return double normalized color value
     */
    double getNormalizedColorValue(RGBWColor color, double normalizedAmbientLight);

    /**
     * @brief Get the sensor's correlated color temperature (CCT) value in Kelvin.
     * 
     * @return double raw cct value in Kelvin
     */
    double getCCT();

    /**
     * @brief Approximate brightness value based on **normalized** RGB values.
     * 
     * This method uses the approximation algorithm proposed in
     * https://www.w3.org/TR/AERT/#color-contrast.
     * The approximated value is normalized to a scale of 0 to 255.
     * 
     * @param red normalized red value
     * @param green normalized green value
     * @param blue normalized blue value
     * @return double approximation for color value
     */
    double calculateBrightness(double red, double green, double blue);

    /**
     * @brief Determine if brightness value represents a white or a black chess
     *        field.
     *
     * Note that the room must be well-lit or color correction light is turned on.
     * At a normalized ambient light of about 10.0 or lower white field will be interpreted as black.
     * 
     * @param brightness normalized brightness value
     * @return true if surface is white-ish
     * @return false if surface is black-ish
     */
    double isWhiteField(double brightness);
};

#endif // ChessColorDetection_h