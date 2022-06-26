#include"Demo.hpp"

namespace Hum{

void testHum(){
    Human people;
    people.setHandRightcb(HugePower);
    people.setHandLeftcb(HugePower);
    people.setLegLeftcb(WenShen);
    people.setLegRightcb(HugePower);

    people.setFunccb(eatshit);    
    //
    people.Run();

}

} 