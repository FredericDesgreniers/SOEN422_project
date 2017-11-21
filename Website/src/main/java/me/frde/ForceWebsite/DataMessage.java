package me.frde.ForceWebsite;

public class DataMessage {
    private String time;
    private float force;
    
    public DataMessage(String time, float force){
        this.time = time;
        this.force = force;
    }
    

    public String getTime() {
        return time;
    }

    public void setTime(String time) {
        this.time = time;
    }

    public float getForce() {
        return force;
    }

    public void setForce(float force) {
        this.force = force;
    }
}
