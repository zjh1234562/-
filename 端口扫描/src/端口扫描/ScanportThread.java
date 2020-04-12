package ¶Ë¿ÚÉ¨Ãè;
import java.awt.Dimension;
import java.awt.Rectangle;
import java.util.ArrayList;

import java.util.List;

import javax.swing.JProgressBar;
import javax.swing.SwingUtilities;

import ¶Ë¿ÚÉ¨Ãè.PortList_and_IPList;
import ¶Ë¿ÚÉ¨Ãè.ScanPort;

public class ScanportThread extends Thread{
	private PortList_and_IPList PortList_and_IPList=new PortList_and_IPList();
	private List<Integer> PortList=new ArrayList();
	private String IP;
	public int n=0;
	private JProgressBar bar;
	
    public void setIP(String IP) {
        this.IP = IP;
    }
    public void setPortList(List<Integer> portList) {
        this.PortList = portList;
    }
    
    public int getn() {
		return this.n;
	}
    
    public void setprobar(JProgressBar bar) {
		this.bar=bar;
	}

    public List<Integer> getPortList() {
        return PortList;
    }
    

    

	
	@Override
	public void run() {
		// TODO Auto-generated method stub
		super.run();
        for(int item:PortList){
        	n=item;
            System.out.println("testing Prot"+item);
            if(ScanPort.ScannerPortisAlive(item,IP)==true){
                PortList_and_IPList.addPort(item);
            }
        }
	}

}
