#ifndef BSP_HPP
#define BSP_HPP

// a very simple Board Support Package (BSP) -------------------------------
class BSP {
public:
    
    static void init(void);
    static void ledOff(void);
    static void ledOn(void);
    static void ledRed(void);
    static void ledGreen(void);
    static void ledBlue(void);
    static void makeNoise(void);
    static void makeEvilNoise(void);
};








#endif // BSP_HPP