package 端口扫描;

import java.awt.TextArea;
import java.awt.TextField;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketAddress;
import java.rmi.UnknownHostException;
import java.sql.Time;
import java.util.ArrayList;
import java.util.List;
import javax.swing.SwingUtilities;

import javax.swing.JProgressBar;
import 端口扫描.ShowProgressBar;

public class ScanPort {
	public TextArea textArea;
	private JProgressBar bar;
	private int n;
	//File file=new File("1.txt");
	
	public ScanPort(TextArea textArea,JProgressBar bar,int n) {
		// TODO Auto-generated constructor stub
		this.textArea=textArea;
		this.bar=bar;
		this.n=n;
	}
	
	public void save(String string) {
		//String string2=string;
		try {
			FileWriter fileWriter=new FileWriter("1.txt",true);
			fileWriter.write(string);
			fileWriter.flush();
			fileWriter.close();
		} catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
		}
	}
	
    static public boolean ScannerPortisAlive(int port,String ip){
        boolean result=true;
        Socket socket=null;
        try{
            socket=new Socket();
            SocketAddress address=new InetSocketAddress(ip, port);
            //socket.getInetAddress();
            socket.connect(address,50);
            socket.close();
//            Socket testPortSocket = new Socket(HostIP, port);
//            testPortSocket.close();
        }catch (IOException e) {
            result =false;
        }
        return result;
    }
    
    public String gethostname(String ip) {
    	try {
    		InetAddress inetAddress=InetAddress.getByName(ip);
    		return inetAddress.getHostName();
    		//System.out.println(inetAddress.getHostName());
		} catch (Exception e) {
			// TODO: handle exception
			return "";
		}
	}
    
    public synchronized void write( String s) {
    	textArea.append(s);
    }

    
    public  void startscan(int startport,int endport,String ip,int blocksize) {
        ThreadManager manager=new ThreadManager();
        List<Integer> runlist=new ArrayList();
  
        long start = System.currentTimeMillis( );
        for(int i=startport;i<=endport;i++){
            runlist.add(i);
            //new ShowProgressBar(bar, blocksize*(endport-startport)).get(i);
            //new ShowProgressBar(bar,blocksize*(endport-startport)).start();
        }
        //String LocalHost=manager.setLocalHostIP();
        manager.ThreadDilivery(runlist,ip,blocksize,n,bar);
        manager.run();
        while (!manager.isDone()){
        }
        long end = System.currentTimeMillis( );
        long diff = end - start;
        System.out.println("处理完成"+diff);
        PortList_and_IPList a=new PortList_and_IPList();
        List<Integer> resultList=a.getOpenPortList();
        for(int Item:resultList){
        	//System.out.println(Item);
        	String string=gethostname(ip);
        	String string2=new IsIP().findServiceByPort(Item);
        	if (string2!="") {
        		textArea.append("主机名："+string+"   "+"PORT:"+Item+"   "+"状态：Open"+"   "+"类型:"+string2.split(" ")[0]+"   "+"服务名称："+string2.split("=")[1]+'\n');
        		String string3="主机名："+string+"   "+"PORT:"+Item+"   "+"状态：Open"+"   "+"类型:"+string2.split(" ")[0]+"   "+"服务名称："+string2.split("=")[1]+'\n';
        		save(string3);
			}
        	else {
        		textArea.append("主机名："+string+"   "+"PORT:"+Item+"   "+"状态：Open"+"   "+"类型:"+string2.split(" ")[0]+"   "+"服务名称："+'\n');
			    String string4="主机名："+string+"   "+"PORT:"+Item+"   "+"状态：Open"+"   "+"类型:"+string2.split(" ")[0]+"   "+"服务名称："+'\n';
			    save(string4);
        	}
        	
        }
        textArea.append("ip:"+ip+"处理时长："+diff+"ms\n");
	}
    

	

}
