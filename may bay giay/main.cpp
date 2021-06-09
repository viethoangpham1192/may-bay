#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cmath>
#include <SFML/Audio.hpp>

using namespace std ;
using namespace sf ;


/*** kiểm tra xem đã ăn được tiền chưa ***/
bool scores ( float x_scores , float y_scores , float x_planes , float y_planes )
{
    float r = 45 /*** r là bán kính của vật phẩm hình tròn ***/ ;
    float d /*** d là khoảng cách từ tâm vật phẩm đến máy bay ***/ ;
    d = sqrt( pow(x_scores - x_planes ,2) + pow( y_scores - y_planes , 2 ) ) ;
    if ( d > r )
        return false ;
    if ( d <= r )
        return true ;

}

bool boom_no ( float x_boom , float y_boom , float x_planes , float y_planes )
{
    float r = 45.5 /*** r là bán kính của boom hình tròn ***/ ;
    float d /*** d là khoảng cách từ tâm boom đến máy bay ***/ ;
    d = sqrt( pow(x_boom - x_planes ,2) + pow( y_boom - y_planes , 2 ) ) ;
    if ( d > r )
        return false ;
    if ( d <= r )
        return true ;

}

/*** dừng chương trình trong một thời gian ***/
void wait(float seconds)
{
	clock_t ew;
	ew = clock() + seconds * CLOCKS_PER_SEC;
	while (clock() < ew) {}
}

int main ()
{
    srand(time(0));
    int diem = 0 , max = 0 ;
    string b ;
    RenderWindow window(VideoMode(600,900) , "MAY BAY GIAY") ;
    Texture h[10] ;
    Font font ;



    font.loadFromFile("Molot.otf") ;
    h[0].loadFromFile("image.png") ;
    h[1].loadFromFile("map.png") ;
    h[2].loadFromFile("boom.png") ;
    h[3].loadFromFile("mainn.png") ;
    h[4].loadFromFile("sound.png") ;
    h[5].loadFromFile("play.png") ;
    h[6].loadFromFile("exit.png") ;
    h[7].loadFromFile("mute.png") ;
    h[8].loadFromFile("mutee.png") ;
    h[9].loadFromFile("coin.png") ;


    Music music , an_diem , die ;
    die.openFromFile("die.wav") ;
    an_diem.openFromFile("a.wav") ;
    music.openFromFile("music.wav") ;
    music.play() ;
    music.setLoop(true) ;



    Sprite backGround(h[1]) , planes(h[0]) , boom[10] , mainn(h[3]) , big(h[5]) , small(h[4]),
    exit(h[6]) , mute(h[7]) , mutee(h[8]) , coin(h[9]) ;

    for ( int n = 0 ; n < 10 ; n++ )
    {
        boom[n].setTexture(h[2]);
    }
    for ( int n = 0 ; n < 10 ; n++ )
    {
        boom[n].setScale(0.5,0.5) ; /** thu nhỏ hình ảnh đi 4 lần **/
        boom[n].setOrigin(109,157) ; /** chỉnh tâm vào giữa hình , vì mặc định tâm của hình là ở góc **/
    }



    backGround.setTextureRect(IntRect(0,1800,600,900)) ;
    mainn.setPosition(300,450) ;
    mainn.setOrigin(240.5,197) ;
    planes.setPosition(300,800) ;
    planes.setOrigin(24,35) ;
    big.setPosition(55,219) ;
    small.setPosition(-25,347) ;
    exit.setPosition(197,412) ;
    mute.setPosition(225,518) ;
    mutee.setPosition(225,518) ;
    coin.setOrigin(450,450) ;
    coin.setScale(0.1,0.1) ;




    float y = 1800 , speed = 0 ;
    bool play = false , up = true , down = false , sound = true , tang_toc = false , pause = false ,
    tha_vat_pham = false, randomViTriThaVatPham = false ;


    while ( window.isOpen() )
    {
        Event e ;
        while ( window.pollEvent(e) )
        {
            if ( e.type == Event::Closed ) window.close() ;
        }

        Text diem_so( "sc " + to_string(diem) + " hi " + to_string(max),font,30) ;
        if ( max < diem ) max = diem ;
        window.clear() ;


        /*************************** background **********************************/

        backGround.setTextureRect(IntRect(0,y,600,900)) ;
        y = y - 0.1 - speed/1.5 ;
        if ( y <= 0 ) y = 1800 ;



        window.draw(backGround) ;

        for ( int n = 0 ; n < 10 ; n++ )
        if ( boom_no( boom[n].getPosition().x , boom[n].getPosition().y , planes.getPosition().x , 765 )
            || boom_no( boom[n].getPosition().x , boom[n].getPosition().y , planes.getPosition().x - 24 , 821 )
            || boom_no( boom[n].getPosition().x , boom[n].getPosition().y , planes.getPosition().x + 24 , 821 ) )
        {
            if (sound)
            {
                die.play() ;
                wait(0.8) ;
            }
            if (!sound)
            {
                wait(0.5) ;
            }
            die.stop() ;
            play = false ;
        }
        if ( scores( coin.getPosition().x , coin.getPosition().y , planes.getPosition().x , 765 )
            || scores( coin.getPosition().x , coin.getPosition().y , planes.getPosition().x - 24 , 821 )
            || scores( coin.getPosition().x , coin.getPosition().y , planes.getPosition().x + 24 , 821 ) )
        {
            if (sound)
            {
                an_diem.play() ;
            }
            diem = diem + 10 ;
            coin.setPosition(1000,901) ;
        }


        /***************************************** Màn Hình chính *****************************************/
        if ( play == false )
        {
            an_diem.stop() ;
            speed = 0 ; /** đưa về tốc độ ban đầu **/
            window.draw(mainn) ;
            boom[0].setPosition(300,0) ;
            boom[1].setPosition(rand()%171 + 30,0) ;
            boom[2].setPosition(rand()%171 + 400,0) ;
            boom[3].setPosition(rand()%201 + 200,0) ;
            boom[4].setPosition(rand()%171 + 30,0) ;
            boom[5].setPosition(rand()%201 + 200,0) ;  /*****  random vị trí cho boom ******/
            boom[6].setPosition(rand()%171 + 400,0) ;
            boom[7].setPosition(rand()%171 + 30,0) ;
            boom[8].setPosition(rand()%201 + 200,0) ;
            boom[9].setPosition(rand()%171 + 400,0) ;
            coin.setPosition(1000,901) ;  /** đưa coin đến toa độ (1000,901) mục đích để tha_vat_pham về false **/


            /** các hoạt động ở màn hình chính **/
            if (up) window.draw(big) ;
            if (down) window.draw(small) ;
            if (!up&&!down) window.draw(exit) ;
            if (Keyboard::isKeyPressed(Keyboard::Enter) && up )
            {
                diem = 0 ;
                play = true ;
            }
            if (Keyboard::isKeyPressed(Keyboard::Down)&&up)
            {
                up = false ;
                down = true ;
            }
            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                up = true ;
                down = false ;
            }
            if (Keyboard::isKeyPressed(Keyboard::Right) && down )
                down = false ;
            if (Keyboard::isKeyPressed(Keyboard::Left) && !down && !up)
                down  = true ;
            if (Keyboard::isKeyPressed(Keyboard::Enter) && !up&&!down )
                window.close() ;
            if (Keyboard::isKeyPressed(Keyboard::Enter) && down && sound )
            {
                sound = false ;
                music.pause() ;
                wait(0.2) ;
            }
            else if (Keyboard::isKeyPressed(Keyboard::Enter) && down && !sound )
            {
                sound = true ;
                music.play() ;
                wait(0.2) ;

            }
            if ( !sound && ( up || !up && !down ) ) window.draw(mute) ;
            if ( !sound && down ) window.draw(mutee) ;

        }
        /*********************************** khi đang chơi game ***********************************************/
        if (play && !pause)
        {
            /** thả rơi iphonex lần lượt **/
            window.draw(boom[0]) ;
            boom[0].move(0,0.2+speed) ;
            if ( boom[0].getPosition().y >= 300 )
            {
                window.draw(boom[1]) ;
                boom[1].move(0,0.2+speed) ;
            }
            if ( boom[1].getPosition().y >= 300 )
            {
                window.draw(boom[2]) ;
                boom[2].move(0,0.2+speed) ;
            }
            if ( boom[2].getPosition().y >= 300 )
            {
                window.draw(boom[3]) ;
                boom[3].move(0,0.2+speed) ;
            }
            if ( boom[3].getPosition().y >= 300 )
            {
                window.draw(boom[4]) ;
                boom[4].move(0,0.2+speed) ;
            }
            if ( boom[4].getPosition().y >= 300 )
            {
                window.draw(boom[5]) ;
                boom[5].move(0,0.2+speed) ;
            }
            if ( boom[4].getPosition().y >= 300 && boom[4].getPosition().y <= 350 )
                randomViTriThaVatPham = true ;  /** bật true để random coin **/
            if ( boom[5].getPosition().y >= 300 )
            {
                window.draw(boom[6]) ;
                boom[6].move(0,0.2+speed) ;
                tha_vat_pham = true ; /** bắt đầu thả coin **/
            }
            if ( boom[6].getPosition().y >= 300 )
            {
                window.draw(boom[7]) ;
                boom[7].move(0,0.2+speed) ;
            }
            if ( boom[7].getPosition().y >= 300 )
            {
                window.draw(boom[8]) ;
                boom[8].move(0,0.2+speed) ;
            }
            if ( boom[8].getPosition().y >= 300 )
            {
                window.draw(boom[9]) ;
                boom[9].move(0,0.2+speed) ;
            }
            if ( boom[9].getPosition().y >= 900 )
            {
                diem = diem + 1 ;
                boom[0].setPosition(rand()%600,0) ;
                boom[1].setPosition(rand()%171 + 30,0) ;
                boom[2].setPosition(rand()%171 + 400,0) ;
                boom[3].setPosition(rand()%201 + 200,0) ;
                boom[4].setPosition(rand()%171 + 30,0) ;
                boom[5].setPosition(rand()%201 + 200,0) ;
                boom[6].setPosition(rand()%171 + 400,0) ;
                boom[7].setPosition(rand()%201 + 200,0) ;
                boom[8].setPosition(rand()%171 + 30,0) ;
                boom[9].setPosition(rand()%171 + 400,0) ;
                an_diem.stop() ;
            }

            for ( int n = 0 ; n < 9 ; n++ )
            {
                if ( boom[n].getPosition().y >= 900 && boom[n].getPosition().y <= 1000 )
                {
                    diem = diem + 1 ;
                    boom[n].setPosition(1000,1001) ;
                }
            }


            /**** tăng tốc trò chơi ****/
            if ( boom[0].getPosition().y == 0 ) tang_toc = true ;
            if (tang_toc)
            {
                speed = speed + 0.05 ;
                tang_toc = false ;
            }



            if (randomViTriThaVatPham)
            {
                coin.setPosition(rand()%600,0) ;
                randomViTriThaVatPham = false ;
            }
            if ( tha_vat_pham )
            {
                window.draw(coin) ;
                coin.move(0,0.5 + speed) ;
            }
            if ( coin.getPosition().y >= 900 )
            {
                tha_vat_pham = false ;
            }



            if (Keyboard::isKeyPressed(Keyboard::Left) && planes.getPosition().x >= 24 )
            planes.move(-0.3,0) ;
            if (Keyboard::isKeyPressed(Keyboard::Right) && planes.getPosition().x <= 575 )
            planes.move(0.3,0) ;
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                pause = true ;
                wait(0.2) ;
            }

            window.draw(planes) ;
        }


        /************************************** Tạm Dừng Game ***********************************************/
        if ( pause && play ) /* màn hình khi tạm dừng game */
        {
            window.draw(mainn) ;
            if (up) window.draw(big) ;
            if (down) window.draw(small) ;
            if (!up&&!down) window.draw(exit) ;
            if (Keyboard::isKeyPressed(Keyboard::Enter) && up )
                pause = false ;
            if (Keyboard::isKeyPressed(Keyboard::Down)&&up)
            {
                up = false ;
                down = true ;
            }
            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                up = true ;
                down = false ;
            }
            if (Keyboard::isKeyPressed(Keyboard::Right) && down )
                down = false ;
            if (Keyboard::isKeyPressed(Keyboard::Left) && !down && !up)
                down  = true ;
            if (Keyboard::isKeyPressed(Keyboard::Enter) && !up&&!down )
                window.close() ;
            if (Keyboard::isKeyPressed(Keyboard::Enter) && down && sound )
            {
                sound = false ;
                music.pause() ;
                wait(0.2) ;

            }
            else if (Keyboard::isKeyPressed(Keyboard::Enter) && down && !sound )
            {
                sound = true ;
                music.play() ;
                wait(0.2) ;

            }
            if ( !sound && ( up || !up && !down ) ) window.draw(mute) ;
            if (!sound&&down) window.draw(mutee) ;
        }
        window.draw(diem_so) ;
        window.display() ;

    }
}
