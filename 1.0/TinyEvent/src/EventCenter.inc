<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/30
 * Time: 下午7:58
 */

namespace Tiny\Event;


use Tiny\Logger;

class EventCenter {

  static public function default() {
    return new EventCenter();
  }

//  public function addListener(Listener $listener) {
//    $listener->getEvent()->addHandler($listener->getClassSign());
//  }
//
//  public function removeListener(Listener $listener) {
//    $listener->getEvent()->removeHandler($listener->getClassSign());
//  }

  public function postEvent(Event $event):bool {
    $result = true;
    /**
     * @var $handlers array[['event'=>Event, 'handlers'=>[]], ...]
     */
    $event_handlers = $event->getHandlers();

    foreach ($event_handlers as $event_handler) {
      foreach ($event_handler['handlers'] as $handler) {
        Logger::getInstance()->debug("postEvent response: Event("
          .$event_handler['event']->getId()
          .")--->Listener(".$handler.")");
        $listener = Listener::New($handler, $event_handler['event']);
        $result = $result && $listener->process();
      }
    }

    return $result;
  }

//  public function postTimerEvent() {
//    $this->postEvent(new TimerEvent(0, [], ""));
//  }

}

