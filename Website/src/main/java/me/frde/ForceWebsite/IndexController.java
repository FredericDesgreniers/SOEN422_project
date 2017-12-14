package me.frde.ForceWebsite;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.messaging.Message;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.messaging.handler.annotation.SendTo;
import org.springframework.messaging.simp.SimpMessagingTemplate;
import org.springframework.scheduling.annotation.EnableScheduling;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.Random;
import java.util.concurrent.atomic.AtomicInteger;

@Controller
@EnableScheduling
public class IndexController {

    AtomicInteger index = new AtomicInteger(0);

    @Autowired
    private SimpMessagingTemplate template;

    @RequestMapping("/")
    public String index(Model model){
        return "index";
    }

    @RequestMapping("/data")
    public ResponseEntity<String> data(@RequestBody String body) {

        template.convertAndSend("/data/sub", new DataMessage(index.getAndIncrement(), Float.valueOf(body)));

        return ResponseEntity.status(200).build();
    }

}
