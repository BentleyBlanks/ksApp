#ifndef KS_SLIDER_H
#define KS_SLIDER_H

#include <ofMain.h>

template<typename T>
class ksSlider_
{
public:
    ksSlider_(string _name, T _min, T _max, T _value, float x, float y, float width, float height);
    
    ksSlider_(string _name, T _min, T _max, T *_value, float x, float y, float width, float height);
    
    virtual void init(string _name, T _min, T _max, T *_value, float x, float y, float width, float height);
    
    void setMaterial(string sliderDownPath, string sliderUpPath, string fontPath, int fontSize);
    
    void setValue(T _value);
    
    T getValue();
    
    T* getValuePtr();
    
    T getIncrement();
    
    void setIncrement(T _increment);
    
    virtual void input(float x, float y);
    
    void update();
    
    // 基准线
    void draw(int x, int y);
    
    void setVisible(bool visible);
    
    bool isVisible();
    
    ofRectangle& getAABB();
    
    // --!神一样的傻逼解决方案 千万别重蹈覆辙 这是个坑……
    // --!一想到后人可能都没人能看的懂这在写什么的时候 我的内心几乎是崩溃的……
    // --!希望你们别看到这行代码 会哭的……除了写代码时的我 估计世界上找不出几个人能在半小时里把这里看懂的人了
    // --!别来找我 我肯定已经不记得我在写什么了
    // --!-----------------------------------------------------------------------------------
    // --!这你妈妈啊 蛇精病啊 跑不跑的出来啊 我tm孩子都八岁了你倒是像模像样的来一下啊
    // --!我尼玛都这样搞了你还是显示不正常 是不是要我喊你爹你才肯正常啊！你是猪吗！
    // --!-----------------------------------------------------------------------------------
    // --!爹啊 你跑一下那……求求你成功那……求求你了那……我快尼玛吐血了啊
    //　　　　　┏┓　　　┏┓
    //　　　　┏┛┻━━━┻┗┓
    //　　　　┃　　　　　　　┃
    //　　　　┃　　　━　　　┃
    //　　　　┃　┳┛　┗┳　┃
    //　　　　┃　　　　　　　┃
    //　　　　┃　　　┻　　　┃
    //　　　　┗━┓　新　┏━┛
    //　　　　　　┃　东　┃
    //　　┏━━━┛　方　┃
    //　┏┫　　　　　神　┃
    //　┗┓　***　兽　┃
    //　　┗┓┏┳━┓┏┏┛
    //　　　┣┣┃　┣┣┃
    //　　　┗┻┛　┗┻┛
    //
    // ┏┛┻━━━┛┻┓
    // ┃｜｜｜｜｜｜｜┃
    // ┃　　　━　　　┃
    // ┃　┳┛ 　┗┳ ┃
    // ┃　　　　　　　┃
    // ┃　　　┻　　　┃
    // ┃　　　　　　　┃
    // ┗━┓　　　┏━┛
    // 　　┃　史　┃
    // 　　┃　诗　┃
    // 　　┃　之　┃
    // 　　┃　宠　┃
    // 　　┃　　　┗━━━┓
    // 　　┃经验与我同在　┣┓
    // 　　┃攻楼专用宠物　┃
    // 　　┗┓┓┏━┳┓┏┛
    // 　　　┃┫┫　┃┫┫
    // 　　　┗┻┛　┗┻┛
    //
    //         //        ..------..
    //  /~~-.-~__-'`-__  ~-.  .-~-.
    // |   /~~~\     / ~~---\|     |
    // |  ||| * |   | | |  * |     |
    // /_-|\ \ /     \ \ \__.|\.  |
    // ~   \~~   |_|   ~~~~ /   ~-.\
    //      ~-.._      _.-~~
    //        .--~~~~~~--.
    //       |  |______|  |
    //        ~-|______|-~
    //          |      |
    //          |______|
    //          |  |   |
    //          |__|___|
    //          |_|| _||
    //          `--'`--'
    //
    //   ___  __ _   ___    _ __  (_)  _ __ ___    __ _  | |__
    //  / __|/ _` | / _ \  | '_ \ | | | '_ ` _ \  / _` | | '_ \
    // | (__| (_| || (_) | | | | || | | | | | | || (_| | | |_) |
    //  \___|\__,_| \___/  |_| |_||_| |_| |_| |_| \__,_| |_.__/
    //
    //
    //        _          _                      _                       _
    //  _ __ (_)  _ __  (_)  _ __ ___    __ _  | |  ___    __ _   ___  | |__
    // | '__|| | | '_ \ | | | '_ ` _ \  / _` | | | / _ \  / _` | / _ \ | '_ \
    // | |   | | | | | || | | | | | | || (_| | | ||  __/ | (_| ||  __/ | |_) |
    // |_|   |_| |_| |_||_| |_| |_| |_| \__,_| |_| \___|  \__, | \___| |_.__/
    //                                                    |___/
    //                                      __
    //    __    __  __    ___         ___  /\_\        ___ ___       __
    //  /'_ `\ /\ \/\ \ /' _ `\     /' _ `\\/\ \     /' __` __`\   /'__`\
    // /\ \L\ \\ \ \_\ \/\ \/\ \    /\ \/\ \\ \ \    /\ \/\ \/\ \ /\ \L\.\_
    // \ \____ \\ \____/\ \_\ \_\   \ \_\ \_\\ \_\   \ \_\ \_\ \_\\ \__/.\_\
    //  \/___L\ \\/___/  \/_/\/_/    \/_/\/_/ \/_/    \/_/\/_/\/_/ \/__/\/_/
    //    /\____/
    //    \_/__/
    //
    //      ___          ___          ___                   ___                              ___          ___
    //     /  /\        /__/\        /__/\                 /__/\       ___                  /__/\        /  /\
    //    /  /:/_       \  \:\       \  \:\                \  \:\     /  /\                |  |::\      /  /::\
    //   /  /:/ /\       \  \:\       \  \:\                \  \:\   /  /:/                |  |:|:\    /  /:/\:\
    //  /  /:/_/::\  ___  \  \:\  _____\__\:\           _____\__\:\ /__/::\              __|__|:|\:\  /  /:/~/::\
    // /__/:/__\/\:\/__/\  \__\:\/__/::::::::\         /__/::::::::\\__\/\:\__          /__/::::| \:\/__/:/ /:/\:\
    // \  \:\ /~~/:/\  \:\ /  /:/\  \:\~~\~~\/         \  \:\~~\~~\/   \  \:\/\         \  \:\~~\__\/\  \:\/:/__\/
    //  \  \:\  /:/  \  \:\  /:/  \  \:\  ~~~           \  \:\  ~~~     \__\::/          \  \:\       \  \::/
    //   \  \:\/:/    \  \:\/:/    \  \:\                \  \:\         /__/:/            \  \:\       \  \:\
    //    \  \::/      \  \::/      \  \:\                \  \:\        \__\/              \  \:\       \  \:\
    //     \__\/        \__\/        \__\/                 \__\/                            \__\/        \__\/
    //
    //
    //    ffffffffffffffff                                                                                  iiii        !!!
    //   f::::::::::::::::f                                                                                i::::i      !!:!!
    //  f::::::::::::::::::f                                                                                iiii       !:::!
    //  f::::::fffffff:::::f                                                                                           !:::!
    //  f:::::f       ffffffaaaaaaaaaaaaa  nnnn  nnnnnnnn       ggggggggg   ggggg     ppppp   ppppppppp   iiiiiii      !:::!
    //  f:::::f             a::::::::::::a n:::nn::::::::nn    g:::::::::ggg::::g     p::::ppp:::::::::p  i:::::i      !:::!
    // f:::::::ffffff       aaaaaaaaa:::::an::::::::::::::nn  g:::::::::::::::::g     p:::::::::::::::::p  i::::i      !:::!
    // f::::::::::::f                a::::ann:::::::::::::::ng::::::ggggg::::::gg     pp::::::ppppp::::::p i::::i      !:::!
    // f::::::::::::f         aaaaaaa:::::a  n:::::nnnn:::::ng:::::g     g:::::g       p:::::p     p:::::p i::::i      !:::!
    // f:::::::ffffff       aa::::::::::::a  n::::n    n::::ng:::::g     g:::::g       p:::::p     p:::::p i::::i      !:::!
    //  f:::::f            a::::aaaa::::::a  n::::n    n::::ng:::::g     g:::::g       p:::::p     p:::::p i::::i      !!:!!
    //  f:::::f           a::::a    a:::::a  n::::n    n::::ng::::::g    g:::::g       p:::::p    p::::::p i::::i       !!!
    // f:::::::f          a::::a    a:::::a  n::::n    n::::ng:::::::ggggg:::::g       p:::::ppppp:::::::pi::::::i
    // f:::::::f          a:::::aaaa::::::a  n::::n    n::::n g::::::::::::::::g       p::::::::::::::::p i::::::i      !!!
    // f:::::::f           a::::::::::aa:::a n::::n    n::::n  gg::::::::::::::g       p::::::::::::::pp  i::::::i     !!:!!
    // fffffffff            aaaaaaaaaa  aaaa nnnnnn    nnnnnn    gggggggg::::::g       p::::::pppppppp    iiiiiiii      !!!
    //                                                                   g:::::g       p:::::p
    //                                                       gggggg      g:::::g       p:::::p
    //                                                       g:::::gg   gg:::::g      p:::::::p
    //                                                        g::::::ggg:::::::g      p:::::::p
    //                                                         gg:::::::::::::g       p:::::::p
    //                                                           ggg::::::ggg         ppppppppp
    //                                                              gggggg
    //
    //
    //
    // '########::'####::::'##:::::::'########:::::'######::::'#######::'##::::'##:
    //  ##.... ##:. ##::::: ##::::::: ##.....:::::'##... ##::'##.... ##: ##:::: ##:
    //  ##:::: ##:: ##::::: ##::::::: ##:::::::::: ##:::..::: ##:::: ##: ##:::: ##:
    //  ########::: ##::::: ##::::::: ######:::::: ##::'####: ##:::: ##: ##:::: ##:
    //  ##.. ##:::: ##::::: ##::::::: ##...::::::: ##::: ##:: ##:::: ##: ##:::: ##:
    //  ##::. ##::: ##::::: ##::::::: ##:::::::::: ##::: ##:: ##:::: ##: ##:::: ##:
    //  ##:::. ##:'####:::: ########: ########::::. ######:::. #######::. #######::
    // ..:::::..::....:::::........::........::::::......:::::.......::::.......:::
    //
    //
    //
    int __T_T___offsetY;
    int __T_T___stickRectY;
protected:
    
#ifdef KS_TARGET_TOUCH
    virtual void onTouchDown(ofTouchEventArgs &data);
    virtual void onTouchMoved(ofTouchEventArgs &data);
    virtual void onTouchUp(ofTouchEventArgs &data);
    virtual void onTouchDoubleTap(ofTouchEventArgs &data);
    virtual void onTouchCancelled(ofTouchEventArgs &data);
    
    virtual void touchDown(float x, float y, int id);
    virtual void touchMoved(float x, float y, int id);
    virtual void touchUp(float x, float y, int id);
    virtual void touchCancelled(float x, float y, int id);
#endif
    virtual void onMousePressed(ofMouseEventArgs& data);
    virtual void onMouseDragged(ofMouseEventArgs& data);
    virtual void onMouseReleased(ofMouseEventArgs& data);
    virtual void onMouseMoved(ofMouseEventArgs& data);
    
    virtual void mouseDragged(int x, int y, int button);
    virtual void mousePressed(int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button);
    virtual void mouseMoved(int x, int y );
    
private:
    ofEvent<ofEventArgs> newGUIEvent;
    
    ofRectangle aabb;
    
    string name;
    int fontSize;
    
    // render
    ofImage sliderDown, sliderUp;
    ofRectangle aabbDown, aabbUp;
    ofTrueTypeFont sliderFont;
    
    bool bVisible, bHit;
    
    // value
    T value, increment;
    T max, min;
};

typedef ksSlider_<int> ksIntSlider;
typedef ksSlider_<float> ksSlider;
typedef ksSlider_<double> ksDoubleSlider;

#endif
