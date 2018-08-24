package net.double_pmcl.maven.mygames;

import java.awt.Color;
import java.awt.Component;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.border.LineBorder;

public class LOGGame extends JFrame {
    // private JFrameLightOffGameAnalyse jframelightoffgameanalyse;
    private boolean iscolor;
    private boolean isnumber;
    private boolean isgamestarted;
    private boolean issolveanimationon;
    private int colormax = 10;
    private int colornow = 2;
    private int fieldsizemax = 20;
    private int fieldsizenow = 5;
    private int menuitemsettingprev = 0;
    private int menuitemsizelistprev = 0;
    private int menuitemcolorlistprev = 0;
    private int h_frame;
    private int w_frame;
    private int t_frame = 300;
    private int l_frame = 200;
    private int x_btn = fieldsizenow;
    private int y_btn = fieldsizenow;
    private int h_btn = 100;
    private int w_btn = h_btn;
//    private int w_btn = 50;
    private int t_btn = 15;
    private int l_btn = 20;
    private int y_btncolor = colormax - 1;
    private int timesleep = 50;
    private int fontsizebtnlist;
    private List<List<Byte>> gamefieldlist = new ArrayList<>();
    private List<List<JButton>> btnlist = new ArrayList<>();
    private List<List<Color>> colorlist = new ArrayList<>();
    private List<Color> colormenuitemlist = new ArrayList<>();
    private JMenuBar menubar = new JMenuBar();
    private Border bordermenubar = new LineBorder(Color.yellow);
    private JMenu menugame = new JMenu("Game");
    private JMenu menusize = new JMenu("Size");
    private JMenu menucolor = new JMenu("Color");
    private JMenu menusolve = new JMenu("Solve");
    private JMenu menusettings = new JMenu("Settings");
    private JMenu menucolorsandnumbers = new JMenu("Colors & Numbers");
    private JMenu menufont = new JMenu("Set Font");
    private JMenu menuhelp = new JMenu("Help");
    private JMenuItem menuitemnewgame = new JMenuItem("New Game");
    private JMenuItem menuitemclearfield = new JMenuItem("Clear");
    private JMenuItem menuitemmix = new JMenuItem("Mix");
    private JMenuItem menuitemshowcolor = new JMenuItem("Show only Color");
    private JMenuItem menuitemshownumber = new JMenuItem("Show only Number");
    private JMenuItem menuitemshowcolornumber = new JMenuItem("Show Color and Number");
    private JMenuItem menuitemexit = new JMenuItem("Exit");
    private JMenuItem menuitemsolveupdown = new JMenuItem("Solve from up to down");
    private JMenuItem menuitemsolvedownup = new JMenuItem("Solve from down to up");
    private JMenuItem menuitemsolveleftright = new JMenuItem("Solve from left to right");
    private JMenuItem menuitemsolverightleft = new JMenuItem("Solve from right to left");
    private JMenuItem menuitemsolveupanddown = new JMenuItem("Solve Up and Down many times");
    private JMenuItem menuitemshowanimation = new JMenuItem("Show Animation");
    private JMenuItem menuitemsetfontsmaller = new JMenuItem("Set Font smaller");
    private JMenuItem menuitemsetfontbigger = new JMenuItem("Set Font bigger");
    private JMenuItem menuiteminfo = new JMenuItem("Info");
    private ArrayList<JMenuItem> menuitemsizelist = new ArrayList<>();
    private ArrayList<JMenuItem> menuitemcolorlist = new ArrayList<>();
    private JSeparator separator1 = new JSeparator();
    private JSeparator separator2 = new JSeparator();
    private JSeparator separator3 = new JSeparator();

    //    private final ScheduledExecutorService scheduler = Executors.newScheduledThreadPool(1);
//scheduler.scheduleAtFixedRate(yourRunnable, 8, 8, HOURS);
    public LOGGame() {
        //commented functions:
        //JOptionPane.showMessageDialog(null, "Finish 4 !!!!", "MessageBox", JOptionPane.PLAIN_MESSAGE);
        // Set beginn values
        isnumber = false;
        iscolor = true;
        isgamestarted = false;
        issolveanimationon = false;
        fontsizebtnlist = 22;
        h_frame = h_btn * y_btn + t_btn * 2 + 85;
        w_frame = w_btn * x_btn + l_btn * 2;
        // this.setBounds(l_frame, t_frame, w_frame, h_frame);
        // Create colorlist
        // hardcoded!!!
        List<Color> all_colors = new ArrayList<Color>() {{
            add(Color.black);
            add(Color.yellow);
            add(Color.darkGray);
            add(Color.gray);
            add(Color.lightGray);
            add(Color.blue);
            add(Color.cyan);
            add(Color.pink);
            add(Color.red);
            add(Color.green);
        }};
        for (int i = 2; i < all_colors.size(); i++) {
            colorlist.add(new ArrayList<Color>(all_colors.subList(0, i)));
        }
        
        // colorlist.add(new ArrayList<Color>());
        // colorlist.get(0).add(Color.black);
        // colorlist.get(0).add(Color.yellow);
        // colorlist.add(new ArrayList<Color>());
        // colorlist.get(1).add(Color.black);
        // colorlist.get(1).add(Color.darkGray);
        // colorlist.get(1).add(Color.yellow);
        // colorlist.add(new ArrayList<Color>());
        // colorlist.get(2).add(Color.black);
        // colorlist.get(2).add(Color.darkGray);
        // colorlist.get(2).add(Color.gray);
        // colorlist.get(2).add(Color.yellow);
        // colorlist.add(new ArrayList<Color>());
        // colorlist.get(3).add(Color.black);
        // colorlist.get(3).add(Color.darkGray);
        // colorlist.get(3).add(Color.gray);
        // colorlist.get(3).add(Color.lightGray);
        // colorlist.get(3).add(Color.yellow);
        // colorlist.add(new ArrayList<Color>());
        // colorlist.get(4).add(Color.black);
        // colorlist.get(4).add(Color.darkGray);
        // colorlist.get(4).add(Color.gray);
        // colorlist.get(4).add(Color.lightGray);
        // colorlist.get(4).add(Color.blue);
        // colorlist.get(4).add(Color.yellow);
        // colorlist.add(new ArrayList<Color>());
        // colorlist.get(5).add(Color.black);
        // colorlist.get(5).add(Color.darkGray);
        // colorlist.get(5).add(Color.gray);
        // colorlist.get(5).add(Color.lightGray);
        // colorlist.get(5).add(Color.blue);
        // colorlist.get(5).add(Color.cyan);
        // colorlist.get(5).add(Color.yellow);
        // colorlist.add(new ArrayList<Color>());
        // colorlist.get(6).add(Color.black);
        // colorlist.get(6).add(Color.darkGray);
        // colorlist.get(6).add(Color.gray);
        // colorlist.get(6).add(Color.lightGray);
        // colorlist.get(6).add(Color.blue);
        // colorlist.get(6).add(Color.cyan);
        // colorlist.get(6).add(Color.pink);
        // colorlist.get(6).add(Color.yellow);
        // colorlist.add(new ArrayList<Color>());
        // colorlist.get(7).add(Color.black);
        // colorlist.get(7).add(Color.darkGray);
        // colorlist.get(7).add(Color.gray);
        // colorlist.get(7).add(Color.lightGray);
        // colorlist.get(7).add(Color.blue);
        // colorlist.get(7).add(Color.cyan);
        // colorlist.get(7).add(Color.pink);
        // colorlist.get(7).add(Color.red);
        // colorlist.get(7).add(Color.yellow);
        // colorlist.add(new ArrayList<Color>());
        // colorlist.get(8).add(Color.black);
        // colorlist.get(8).add(Color.darkGray);
        // colorlist.get(8).add(Color.gray);
        // colorlist.get(8).add(Color.lightGray);
        // colorlist.get(8).add(Color.blue);
        // colorlist.get(8).add(Color.cyan);
        // colorlist.get(8).add(Color.pink);
        // colorlist.get(8).add(Color.red);
        // colorlist.get(8).add(Color.green);
        // colorlist.get(8).add(Color.yellow);
        colormenuitemlist.add(Color.green);
        colormenuitemlist.add(new Color(0xFFFF0000));
        // Set listgamefield
        for (int j = 0; j < fieldsizemax; j++) {
            gamefieldlist.add(new ArrayList<Byte>());
            for (int i = 0; i < fieldsizemax; i++) {
                gamefieldlist.get(j).add((byte) 0);
            }
        }
        // Create btnlist
        for (int j = 0; j < fieldsizemax; j++) {
            btnlist.add(new ArrayList<JButton>());
            for (int i = 0; i < fieldsizemax; i++) {
                JButton new_btn = new JButton();
                new_btn.setBounds(l_btn + w_btn * i, t_btn + h_btn * j, w_btn, h_btn);
                new_btn.setText("0");
                new_btn.setBackground(colorlist.get(colornow - 2).get(0));
                new_btn.setFont(new_btn.getFont().deriveFont((float) fontsizebtnlist));
                new_btn.addActionListener(new BtnList_Click(i, j));
                new_btn.setVisible(false);
                new_btn.setBorder(new LineBorder(Color.white, 1));
                btnlist.get(j).add(new_btn);
                this.add(new_btn);
            }
        }
        // Set Menubar with Border and Menus and MenuItems
        menubar.setBorder(bordermenubar);
        menuitemnewgame.addActionListener(new MenuItemNewGame_Click());
        menugame.add(menuitemnewgame);
        menuitemclearfield.addActionListener(new MenuItemFreeToPlay_Click());
        menugame.add(separator1);
        menugame.add(menuitemclearfield);
        menuitemmix.addActionListener(new MenuItemMix_Click());
        menugame.add(menuitemmix);
        menugame.add(separator2);
        menuitemexit.addActionListener(new MenuItemExit_Click());
        menugame.add(menuitemexit);
        menubar.add(menugame);
        for (int i = 0; i < fieldsizemax - 1; i++) {
            menuitemsizelist.add(new JMenuItem((i + 2) + " x " + (i + 2) + " Size"));
            menuitemsizelist.get(i).addActionListener(new MenuItemSizeList_Click(i));
            if (i == 3) {
                menuitemsizelist.get(fieldsizenow - 2).setBackground(colormenuitemlist.get(0));
                menuitemsizelistprev = fieldsizenow - 2;
            }
            menusize.add(menuitemsizelist.get(i));
        }
        //menusize.add();
        menubar.add(menusize);
        for (int i = 0; i < colormax - 1; i++) {
            menuitemcolorlist.add(new JMenuItem((i + 2) + " Colors"));
            menuitemcolorlist.get(i).addActionListener(new MenuItemColorList_Click(i));
            if (i == 0) {
                menuitemcolorlist.get(0).setBackground(colormenuitemlist.get(0));
                menuitemcolorlistprev = 0;
            }
            menucolor.add(menuitemcolorlist.get(i));
        }
        menubar.add(menucolor);
        menuitemsolveupdown.addActionListener(new MenuItemSolveUpDown_Click());
//        menuitemsolveupdown.addKeyListener(null);
        menusolve.add(menuitemsolveupdown);
        menuitemsolvedownup.addActionListener(new MenuItemSolveDownUp_Click());
//        menuitemsolvedownup.setFocusable(true);
//        menuitemsolvedownup.addKeyListener(new MenuItemSolveDownUp_Key());
        menusolve.add(menuitemsolvedownup);
        menuitemsolveleftright.addActionListener(new MenuItemSolveLeftRight_Click());
        menusolve.add(menuitemsolveleftright);
        System.out.println("Added menuitemsolveleftright");
        menuitemsolverightleft.addActionListener(new MenuItemSolveRightLeft_Click());
        menusolve.add(menuitemsolverightleft);
        menuitemsolveupanddown.addActionListener(new MenuItemSolveUpAndDown_Click());
        menusolve.add(menuitemsolveupanddown);
        menusolve.add(separator3);
//        menuitemshowanimation.setBackground(colormenuitemlist.get(0));
        menuitemshowanimation.addActionListener(new MenuItemShowAnimation_Click());
        menusolve.add(menuitemshowanimation);
        menubar.add(menusolve);
        menuitemshowcolor.addActionListener(new MenuItemShowColor_Click());
        menuitemshowcolor.setBackground(colormenuitemlist.get(0));
        menucolorsandnumbers.add(menuitemshowcolor);
        menuitemshownumber.addActionListener(new MenuItemShowNumber_Click());
        menucolorsandnumbers.add(menuitemshownumber);
        menuitemshowcolornumber.addActionListener(new MenuItemShowColorNumber_Click());
        menucolorsandnumbers.add(menuitemshowcolornumber);
        menusettings.add(menucolorsandnumbers);
        menuitemsetfontsmaller.addActionListener(new MenuItemSetFontSmaller_Click());
        menufont.add(menuitemsetfontsmaller);
        menuitemsetfontbigger.addActionListener(new MenuItemSetFontBigger_Click());
        menufont.add(menuitemsetfontbigger);
        menusettings.add(menufont);
        menubar.add(menusettings);
        menuiteminfo.addActionListener(new MenuItemInfo_Click());
        menuhelp.add(menuiteminfo);
        menubar.add(menuhelp);
        this.setJMenuBar(menubar);
        this.addWindowListener(new WindowEventHandler());
        this.setTitle("Light Off Game - by Haris Ziko");
        this.setBounds(l_frame, t_frame, w_frame, h_frame);
        this.setLayout(null);
        this.setResizable(false);
        refreshFieldPosition();
        refreshFieldView();
        refreshFieldButtons();
        // jframelightoffgameanalyse = new JFrameLightOffGameAnalyse(this.getBounds());
        // jframelightoffgameanalyse.setVisible(false);
    }

    public static void main(String[] args) {
        LOGGame mygame = new LOGGame();
        mygame.setVisible(true);
    }

    public void refreshFieldPosition() {
        if (fieldsizenow <= 10) {
            h_btn = 60;
            w_btn = 60;
        } else if (fieldsizenow <= 20) {
            h_btn = 50;
            w_btn = 50;
        } else if (fieldsizenow <= 30) {
            h_btn = 35;
            w_btn = 35;
        }
        for (int j = 0; j < fieldsizemax; j++) {
            for (int i = 0; i < fieldsizemax; i++) {
                btnlist.get(j).get(i).setBounds(l_btn + w_btn * i, t_btn + h_btn * j, w_btn, h_btn);
            }
        }
    }

    public void refreshFieldView() {
        int leftprev = this.getX();
        int topprev = this.getY();
        for (int j = 0; j < fieldsizemax; j++) {
            for (int i = 0; i < fieldsizemax; i++) {
                if ((i < x_btn) && (j < y_btn)) {
                    btnlist.get(j).get(i).setVisible(true);
                } else {
                    btnlist.get(j).get(i).setVisible(false);
                }
            }
        }
        h_frame = h_btn * y_btn + t_btn * 2 + 46;
        w_frame = w_btn * x_btn + l_btn * 2 + 4;
        System.out.format("h_frame: %d, w_frame: %d\n", h_frame, w_frame);
        System.out.format("h_btn: %d, w_btn: %d, t_btn: %d, l_btn: %d, menubar.getHeight(): %d\n", h_btn, w_btn, t_btn, l_btn, menubar.getHeight());
        if (w_frame < 280) {
            w_frame = 280;
        }
        this.setSize(w_frame, h_frame);
        this.setLocation(leftprev, topprev);
    }

    public void refreshFieldButtons() {
        for (int j = 0; j < y_btn; j++) {
            for (int i = 0; i < x_btn; i++) {
                if (iscolor) {
                    btnlist.get(j).get(i).setBackground(colorlist.get(colornow - 2).get(gamefieldlist.get(j).get(i)));
                } else {
                    btnlist.get(j).get(i).setBackground(UIManager.getColor("Button.background"));
                }
                if (isnumber) {
                    btnlist.get(j).get(i).setText(String.valueOf(gamefieldlist.get(j).get(i)));
                } else {
                    btnlist.get(j).get(i).setText("");
                }
            }
        }
    }

    public void mixField() {
        Random r = new Random();
        for (int i = 0; i < fieldsizenow * fieldsizenow * 10; i++) {
            changeFieldColorCross(r.nextInt(x_btn), r.nextInt(y_btn));
        }
    }

    public void clearField() {
        for (int j = 0; j < fieldsizemax; j++) {
            for (int i = 0; i < fieldsizemax; i++) {
                gamefieldlist.get(j).set(i, (byte) 0);
            }
        }
    }

    public void changeFieldColor(int x, int y) {
        gamefieldlist.get(y).set(x, (byte) (gamefieldlist.get(y).get(x) + 1));
        if (gamefieldlist.get(y).get(x) >= colornow) {
            gamefieldlist.get(y).set(x, (byte) 0);
        }
    }

    public void changeFieldColorCross(int x, int y) {
        changeFieldColor(x, y);
        if (x > 0) {
            changeFieldColor(x - 1, y);
        }
        if (y > 0) {
            changeFieldColor(x, y - 1);
        }
        if (x < x_btn - 1) {
            changeFieldColor(x + 1, y);
        }
        if (y < y_btn - 1) {
            changeFieldColor(x, y + 1);
        }
    }

    public void resetField() {
        for (int j = 0; j < y_btn; j++) {
            for (int i = 0; i < x_btn; i++) {
                gamefieldlist.get(j).set(i, (byte) 0);
            }
        }
    }

    public void pauseProgram(long millisec) {
        /*for (long i = 0; i < 100000 * millisec; i++)
        {}*/
        synchronized (Thread.currentThread()) {
            try {
                wait();
            } catch (InterruptedException e) {
            }
        }
    }

    class WindowEventHandler extends WindowAdapter {
        @Override
        public void windowClosing(WindowEvent evt) {
            System.exit(0);
        }
    }

    class DrawingComponent extends Component {
        @Override
        public void paint(Graphics g) {
            Graphics2D g2d = (Graphics2D) g;
            g2d.drawLine(0, 0, 2, 2);
        }
    }

    class BtnList_Click implements ActionListener {
        int ID_btnx = 0;
        int ID_btny = 0;

        public BtnList_Click(int setIDx, int setIDy) {
            ID_btnx = setIDx;
            ID_btny = setIDy;
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            //pressButton(ID_btnx, ID_btny);
            changeFieldColorCross(ID_btnx, ID_btny);
            refreshFieldButtons();
        }
    }

    class MenuItemNewGame_Click implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            mixField();
            //iscolor = true;
            //isnumber = false;
            refreshFieldView();
            refreshFieldButtons();
        }
    }

    class MenuItemFreeToPlay_Click implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            clearField();
            //iscolor = true;
            //isnumber = false;
            refreshFieldView();
            refreshFieldButtons();
        }
    }

    class MenuItemMix_Click implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            mixField();
            refreshFieldButtons();
        }
    }

    class MenuItemShowColor_Click implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            iscolor = true;
            isnumber = false;
            if (menuitemsettingprev != 0) {
                menuitemshowcolor.setBackground(colormenuitemlist.get(0));
                menuitemshownumber.setBackground(UIManager.getColor("Button.background"));
                menuitemshowcolornumber.setBackground(UIManager.getColor("Button.background"));
                menuitemsettingprev = 0;
            }
            refreshFieldButtons();
        }
    }

    class MenuItemShowNumber_Click implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            iscolor = false;
            isnumber = true;
            if (menuitemsettingprev != 1) {
                menuitemshowcolor.setBackground(UIManager.getColor("Button.background"));
                menuitemshownumber.setBackground(colormenuitemlist.get(0));
                menuitemshowcolornumber.setBackground(UIManager.getColor("Button.background"));
                menuitemsettingprev = 1;
            }
            refreshFieldButtons();
        }
    }

    class MenuItemShowColorNumber_Click implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            iscolor = true;
            isnumber = true;
            if (menuitemsettingprev != 2) {
                menuitemshowcolor.setBackground(UIManager.getColor("Button.background"));
                menuitemshownumber.setBackground(UIManager.getColor("Button.background"));
                menuitemshowcolornumber.setBackground(colormenuitemlist.get(0));
                menuitemsettingprev = 2;
            }
            refreshFieldButtons();
        }
    }

    class MenuItemExit_Click implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            System.exit(0);
        }
    }

    class MenuItemSizeList_Click implements ActionListener {
        int ID_number = 0;

        public MenuItemSizeList_Click(int setID) {
            ID_number = setID;
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            fieldsizenow = ID_number + 2;
            x_btn = fieldsizenow;
            y_btn = fieldsizenow;
            Color temp;
            temp = menuitemsizelist.get(menuitemsizelistprev).getBackground();
            menuitemsizelist.get(menuitemsizelistprev).setBackground(
                    menuitemsizelist.get(ID_number).getBackground());
            menuitemsizelist.get(ID_number).setBackground(temp);
            menuitemsizelistprev = ID_number;
            resetField();
            refreshFieldPosition();
            refreshFieldView();
            refreshFieldButtons();
        }
    }

    class MenuItemColorList_Click implements ActionListener {
        int ID_number = 0;

        public MenuItemColorList_Click(int setIDy) {
            ID_number = setIDy;
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            colornow = ID_number + 2;
            Color temp;
            temp = menuitemcolorlist.get(menuitemcolorlistprev).getBackground();
            menuitemcolorlist.get(menuitemcolorlistprev).setBackground(
                    menuitemcolorlist.get(ID_number).getBackground());
            menuitemcolorlist.get(ID_number).setBackground(temp);
            menuitemcolorlistprev = ID_number;
            resetField();
            refreshFieldButtons();
        }
    }

    public void solveUpToDown() {
        for (int j = 1; j < fieldsizenow; j++) {
            for (int i = 0; i < fieldsizenow; i++) {
                try {
                    if (gamefieldlist.get(j - 1).get(i).intValue() != 0) {
                        btnlist.get(j).get(i).setBackground(Color.magenta);
                        if (issolveanimationon) {
                            Thread.sleep(timesleep);
                        }
                        btnlist.get(j).get(i).setBackground(colorlist.get(colornow - 2).get(gamefieldlist.get(j).get(i).intValue()));
                        while (gamefieldlist.get(j - 1).get(i).equals((byte) 0) != true) {
                            changeFieldColorCross(i, j);
                            refreshFieldButtons();
                        }
                        if (issolveanimationon) {
                            Thread.sleep(timesleep);
                        }
                    }
                } catch (Exception ex) {
                }
            }
        }
    }

    private void solveDownToUp() {
        for (int j = fieldsizenow - 2; j >= 0; j--) {
            for (int i = fieldsizenow - 1; i >= 0; i--) {
                try {
                    if (gamefieldlist.get(j + 1).get(i).intValue() != 0) {
                        btnlist.get(j).get(i).setBackground(Color.magenta);
                        if (issolveanimationon) {
                            Thread.sleep(timesleep);
                        }
                        btnlist.get(j).get(i).setBackground(colorlist.get(colornow - 2).get(gamefieldlist.get(j).get(i).intValue()));
                        while (gamefieldlist.get(j + 1).get(i).equals((byte) 0) != true) {
                            changeFieldColorCross(i, j);
                            refreshFieldButtons();
                        }
                        if (issolveanimationon) {
                            Thread.sleep(timesleep);
                        }
                    }
                } catch (Exception ex) {
                }
            }
        }
    }

    private void solveLeftToRight() {
        for (int i = 1; i < fieldsizenow; i++) {
            for (int j = 0; j < fieldsizenow; j++) {
                try {
                    if (gamefieldlist.get(j).get(i-1).intValue() != 0) {
                        btnlist.get(j).get(i).setBackground(Color.magenta);
                        if (issolveanimationon) {
                            Thread.sleep(timesleep);
                        }
                        btnlist.get(j).get(i).setBackground(colorlist.get(colornow - 2).get(gamefieldlist.get(j).get(i).intValue()));
                        while (gamefieldlist.get(j).get(i-1).equals((byte) 0) != true) {
                            changeFieldColorCross(i, j);
                            refreshFieldButtons();
                        }
                        if (issolveanimationon) {
                            Thread.sleep(timesleep);
                        }
                    }
                } catch (Exception ex) {
                }
            }
        }
    }

    private void solveRightToLeft() {
        for (int i = fieldsizenow - 2; i >= 0; i--) {
            for (int j = fieldsizenow - 1; j >= 0; j--) {
                try {
                    if (gamefieldlist.get(j).get(i+1).intValue() != 0) {
                        btnlist.get(j).get(i).setBackground(Color.magenta);
                        if (issolveanimationon) {
                            Thread.sleep(timesleep);
                        }
                        btnlist.get(j).get(i).setBackground(colorlist.get(colornow - 2).get(gamefieldlist.get(j).get(i).intValue()));
                        while (gamefieldlist.get(j).get(i+1).equals((byte) 0) != true) {
                            changeFieldColorCross(i, j);
                            refreshFieldButtons();
                        }
                        if (issolveanimationon) {
                            Thread.sleep(timesleep);
                        }
                    }
                } catch (Exception ex) {
                }
            }
        }
    }

    class MenuItemSolveUpDown_Click implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            new Thread(new Runnable() {
                @Override
                public void run() {
                    solveUpToDown();
                }
            }).start();
        }
    }

    class MenuItemSolveDownUp_Click implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            new Thread(new Runnable() {
                @Override
                public void run() {
                    solveDownToUp();
                }
            }).start();
        }
    }

    class MenuItemSolveLeftRight_Click implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            new Thread(new Runnable() {
                @Override
                public void run() {
                    solveLeftToRight();
                }
            }).start();
        }
    }

    class MenuItemSolveRightLeft_Click implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            new Thread(new Runnable() {
                @Override
                public void run() {
                    solveRightToLeft();
                }
            }).start();
        }
    }

    class MenuItemSolveDownUp_Key implements KeyListener {
        @Override
        public void keyTyped(KeyEvent e) {

        }

        @Override
        public void keyPressed(KeyEvent e) {
            if (e.getKeyCode() == KeyEvent.VK_W) {
                for (int j = fieldsizenow - 2; j >= 0; j--) {
                    for (int i = fieldsizenow - 1; i >= 0; i--) {
                        btnlist.get(j).get(i).setBackground(Color.magenta);
                        btnlist.get(j).get(i).setBackground(colorlist.get(colornow - 2).get(gamefieldlist.get(j).get(i).intValue()));
                        while (gamefieldlist.get(j + 1).get(i).equals((byte) 0) != true) {
                            changeFieldColorCross(i, j);
                            refreshFieldButtons();
                        }
                    }
                }
            }
        }

        @Override
        public void keyReleased(KeyEvent e) {

        }
    }

    class MenuItemSolveUpAndDown_Click implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            for (int k = 0; k < 100; k++) {
                changeFieldColorCross(0, 0);
                solveUpToDown();
                solveLeftToRight();
                solveDownToUp();
                solveRightToLeft();
            }
        }
    }

    class MenuItemShowAnimation_Click implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            if (issolveanimationon == true) {
                menuitemshowanimation.setBackground(UIManager.getColor("Button.background"));
                issolveanimationon = false;
            } else {
                menuitemshowanimation.setBackground(colormenuitemlist.get(0));
                issolveanimationon = true;
            }
        }
    }

    class MenuItemSetFontSmaller_Click implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            fontsizebtnlist--;
            if (fontsizebtnlist < 10) {
                fontsizebtnlist = 10;
            }
            for (int j = 0; j < fieldsizemax; j++) {
                for (int i = 0; i < fieldsizemax; i++) {
                    btnlist.get(j).get(i).setFont(btnlist.get(j).get(i).getFont().deriveFont((float) fontsizebtnlist));
                }
            }
        }
    }

    class MenuItemSetFontBigger_Click implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            fontsizebtnlist++;
            if (fontsizebtnlist > 30) {
                fontsizebtnlist = 30;
            }
            for (int j = 0; j < fieldsizemax; j++) {
                for (int i = 0; i < fieldsizemax; i++) {
                    btnlist.get(j).get(i).setFont(btnlist.get(j).get(i).getFont().deriveFont((float) fontsizebtnlist));
                }
            }
        }
    }

    class MenuItemInfo_Click implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            JOptionPane.showMessageDialog(null,
                    "This Game was created on 17.04.2014\n" +
                            "Last changes: 24.04.2014,11:30\n" +
                            "Chnages: Implemented line border for the buttons and implemented setfont for changing the font size!\n" +
                            "by Ziko Haris",
                    "MessageBox", JOptionPane.PLAIN_MESSAGE);
        }
    }
}
