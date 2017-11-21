package me.frde.ForceWebsite;

import org.springframework.messaging.Message;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.messaging.handler.annotation.SendTo;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@Controller
public class IndexController {
    @RequestMapping("/")
    public String index(Model model){
        return "index";
    }
    
    @MessageMapping("/dataStream")
    @SendTo("/data/messages")
    public DataMessage send(final Message message )throws Exception{
        return new DataMessage("A time", 3.0f);
    }
}
