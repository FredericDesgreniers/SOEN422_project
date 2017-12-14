package me.frde.ForceWebsite;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.messaging.simp.SimpMessagingTemplate;
import org.springframework.scheduling.annotation.EnableScheduling;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Service;

import java.util.Random;
import java.util.concurrent.atomic.AtomicInteger;

@Service
@EnableScheduling
public class DataService {

    AtomicInteger index = new AtomicInteger(0);

    @Autowired
    private SimpMessagingTemplate template;


    public void boardcastMessage()throws Exception{
        Random r = new Random(System.currentTimeMillis());
        template.convertAndSend("/data/sub", new DataMessage(index.getAndIncrement(), r.nextFloat()));
    }
}
