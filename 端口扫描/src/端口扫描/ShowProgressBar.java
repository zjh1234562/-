package 端口扫描;
import java.awt.Dimension;
import java.awt.Rectangle;

import javax.swing.JProgressBar;

import 端口扫描.Mainwindows;

public class ShowProgressBar extends Thread{
	private JProgressBar bar;
	private int maxnum;
	//public int n;
	private int i=0;
	
	public ShowProgressBar(JProgressBar progressBar,int maxnum) {
		// TODO Auto-generated constructor stub
		this.bar=progressBar;
		this.maxnum=maxnum;
	}
	
	
	public void get(int i) {
		this.i=i;
	}


	

	@Override
	public void run() {
		// TODO Auto-generated method stub
		super.run();
		//bar.setValue(0);
		bar.setStringPainted(true);
		Dimension d = bar.getSize();
		Rectangle rect = new Rectangle(0, 0, d.width, d.height);
//		for (int j=0; j< 100; j++) {
//			try {
//				bar.setValue(i);
//				bar.paintImmediately(rect);
//				Thread.sleep(1);
//			} catch (Exception e) {
//				// TODO: handle exception
//				e.printStackTrace();
//			}
//
//		}

		for(int j=0;j<2*maxnum;j++){
			try {
				bar.setValue(j);
				bar.paintImmediately(rect);
				//Thread.sleep(-1);
			
			} catch (Exception e) {
				// TODO: handle exception
				e.printStackTrace();
			}
		}
		bar.setString("运行完成");
	}

}
