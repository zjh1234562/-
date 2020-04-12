package hhjk;

import java.io.IOException;
import java.net.UnknownHostException;

public class ClientThraed3 extends Thread{

    Mainwindows client;
	public ClientThraed3(Mainwindows client) throws UnknownHostException, IOException { 
		this.client=client; 
	}
	@Override

	public void run() {
		try{
			MySocket mt = new MySocket(client);
	        Thread t = new Thread(mt);
	        t.start();
        }
        catch(Exception e){
            System.out.println("找不到发送方");
        }

	}

}
