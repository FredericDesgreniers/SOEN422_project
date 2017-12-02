package me.frde.ForceWebsite;

public class DataMessage {
    private int time;
    private float force;
    
    public DataMessage(int time, float force){
        this.time = time;
        this.force = force;
    }
    

    public int getTime() {
        return time;
    }

    public void setTime(int time) {
        this.time = time;
    }

    public float getForce() {
        return force;
    }

    public void setForce(float force) {
        this.force = force;
    }
}
