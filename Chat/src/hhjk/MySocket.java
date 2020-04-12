package hhjk;

import java.io.*;
import java.net.*;

class MySocket implements Runnable
{
	Mainwindows cilent;
	public MySocket(Mainwindows cilent) {
		// TODO Auto-generated constructor stub
		this.cilent=cilent;
	}
    public void run(){
        try{
            DatagramSocket socket = new DatagramSocket();
            String line=cilent.txt_message.getText();
            byte[] arr = line.getBytes();
            DatagramPacket packet = new DatagramPacket(arr,arr.length,InetAddress.getByName("192.168.20.1"),11113);
            socket.send(packet);
        }
        catch(Exception e){
            System.out.println("找不到发送方");
        }
    }
}


