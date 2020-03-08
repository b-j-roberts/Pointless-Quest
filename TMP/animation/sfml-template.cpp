#include "../Pointless-Quest/Resources/Resources.h"

int main() {


  sf::RenderWindow window(sf::VideoMode(1200, 800), "Animation Test"); // TO DO : Choose window style
  //sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
  //sf:::RenderWindow window(desktop, "TEMPLATE");

  size_t framerate = 60;
  window.setFramerateLimit(framerate);

  // window size and scale
  const sf::Vector2u window_size(window.getSize());
  const float x_scale(window_size.x * 1.f / window_size.y);

  Texture_Obj swamp_tree_bot_t(128, 64, 3, "SwampTreeBottom");
  Sprite_Obj swamp_tree_bot(31, 110, 1, 1, swamp_tree_bot_t);
  size_t count = 3;
  size_t pos = 0;
  size_t frame_inc = 0; 
  size_t fps = 2;
  while(pos++ < count) {
    swamp_tree_bot.get_Ptr(pos - 1)->setPosition(sf::Vector2f(200, 200));
  }
  pos = 0;

  // Game loop
  sf::Event event;

  while(window.isOpen()) {

    // Input
    while(window.pollEvent(event)) {
      switch(event.type) {

        case sf::Event::KeyPressed:
          switch(event.key.code) {
            case sf::Keyboard::W:
              break;
            // ...
            default: break;
          }
          break; // key pressed

          case sf::Event::Closed:
            window.close();
            break;

        default: break;
      }
    } // end event loop


    // Update


    // Draw
    window.clear();

    window.draw(*swamp_tree_bot.get_Ptr(pos));
    if(++frame_inc == framerate / fps) {
      frame_inc = 0;
      ++pos; 
    };
    if(pos == count) pos = 0;  

    window.display();

  } // end game loop

  return 0;

}
