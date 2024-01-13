using System;
using System.IO;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace image_appv1._0
{
    
    public partial class Form1 : Form
    {
        int BrightNum = 1;
        int RedNum = 1;
        int GreenNum = 1;
        int BlueNum = 1;
        int AngleNum = 0;
        int SizeNum = 100;
        double GammaNum = 1;
        bool NegativeBool = false;
        bool GrayScaleBool = false;
        bool MosaicBool = false;
        bool SharpenBool = false;
        bool BlurBool = false;
        private string inputPath = string.Empty;
        private string outputPath = string.Empty;
        private string tempPath = string.Empty;
        private string tempPath_ = string.Empty;

        [DllImport("Function_01.dll", CallingConvention = CallingConvention.Cdecl,CharSet = CharSet.Ansi)]
        public static extern void Brightness(string inputFilename, string outputFilename, int alpha);
        [DllImport("Function_01.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern void AdjustRedChannel(string inputFilename, string outputFilename, int alpha);
        [DllImport("Function_01.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern void AdjustGreenChannel(string inputFilename, string outputFilename, int alpha);
        [DllImport("Function_01.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern void AdjustBlueChannel(string inputFilename, string outputFilename, int alpha);
        [DllImport("Function_01.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern void RotateImg(string inputFilename, string outputFilename, int angle);
        [DllImport("Function_01.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern void ResizeImg(string inputFilename, string outputFilename, int newSize);
        [DllImport("Function_01.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern void toNegative(string inputFilename, string outputFilename);
        [DllImport("Function_01.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern void toGrayScale(string inputFilename, string outputFilename);
        [DllImport("Function_01.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern void toMosaic(string inputFilename, string outputFilename);
        [DllImport("Function_01.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern void SharpenImage(string inputFilename, string outputFilename);
        [DllImport("Function_01.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern void BlurImage(string inputFilename, string outputFilename);
        [DllImport("Function_01.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern void GammaCorrection(string inputFilename, string outputFilename, double gamma);
        
        public Form1()
        {
            InitializeComponent();
        }
        
        private void toolStripDropDownButton1_Click(object sender, EventArgs e)
        {
            
        }
        private void UploadImageChange(PictureBox pictureBox)
        {
            File.Copy(inputPath, tempPath, true);
            if(RedNum!=1)
                AdjustRedChannel(tempPath, tempPath, RedNum);
            if (GreenNum != 1)
                AdjustGreenChannel(tempPath, tempPath, GreenNum);
            if (BlueNum != 1)
                AdjustBlueChannel(tempPath, tempPath, BlueNum);
            if (BrightNum != 1)
                Brightness(tempPath, tempPath, BrightNum);
            if(AngleNum != 0)
                RotateImg(tempPath, tempPath, AngleNum);
            if(SizeNum != 100)
                ResizeImg(tempPath, tempPath, SizeNum);
            if (GammaNum != 1)
                GammaCorrection(tempPath, tempPath, GammaNum);
            if (NegativeBool == true)
                toNegative(tempPath, tempPath);
            if (GrayScaleBool == true)
                toGrayScale(tempPath, tempPath);
            if (MosaicBool == true)
                toMosaic(tempPath, tempPath);
            if (SharpenBool == true)
                SharpenImage(tempPath, tempPath);
            if (BlurBool == true)
                BlurImage(tempPath, tempPath);
            UpdateImage(tempPath, pictureBox);
        }

        private void OpenImage()
        {
            OpenFileDialog ofDialog = new OpenFileDialog();
            if (ofDialog.ShowDialog() == DialogResult.OK)
            {
                inputPath = ofDialog.FileName;
                tempPath = Path.Combine(Path.GetDirectoryName(Application.ExecutablePath), "TempImage.jpg");
                File.Copy(inputPath, tempPath, true);
                tempPath_ = Path.Combine(Path.GetDirectoryName(Application.ExecutablePath), "TempImage_.jpg");
                File.Copy(tempPath, tempPath_, true);
                UpdateImage(inputPath,pictureBox1);
                reSetAllSet();
                setPicBox();
            }
        }
        private void UpdateImage(string filePath,PictureBox picturebox)
        {
            FileStream fileStream = new FileStream(filePath, FileMode.Open, FileAccess.Read);
            picturebox.Image = System.Drawing.Image.FromStream(fileStream);
            fileStream.Close();
            fileStream.Dispose();
        }

        private void SaveImage(int sw)
        {
            if (!string.IsNullOrEmpty(inputPath))
            {
                if(outputPath == string.Empty || sw == 1)
                {
                    SaveFileDialog saveDialog = new SaveFileDialog();
                    saveDialog.Filter = "Image Files (*.bmp, *.jpg, *.png)|*.bmp;*.jpg;*.png|All files (*.*)|*.*";

                    if (saveDialog.ShowDialog() == DialogResult.OK)
                    {
                        // pictureBox1.Image.Save(saveDialog.FileName);
                        File.Copy(tempPath, saveDialog.FileName, true);
                        outputPath = saveDialog.FileName;
                    }
                }
                else
                {
                    File.Copy(tempPath, outputPath, true);
                    MessageBox.Show("儲存成功.", "訊息", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
                }
            }
            else
            {
                MessageBox.Show("Please open an image first.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void 開啟檔案ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenImage();
        }

        private void 儲存檔案ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveImage(0);
        }

        private void 另存新黨ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveImage(1);
        }

        private void TogglePanelVisibility(Button button, Panel panel)
        {
            if(inputPath == string.Empty)
            {
                MessageBox.Show("請先開啟檔案!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                panel.Visible = !panel.Visible;
                if (panel.Visible)
                {
                    button.Height = 30;
                    button.BackColor = System.Drawing.SystemColors.ControlLight;
                }
                else
                {
                    button.BackColor = System.Drawing.SystemColors.Control;
                    button.Height = 50;
                }
            }
        }
        private void ResetBarText(TrackBar trackbar, TextBox textbox)
        {
            trackbar.Value = 1;
            textbox.Text = "1";
        }
        private bool TrackBarValueToText(TrackBar trackbar,TextBox textbox)
        {
            if (tempPath == string.Empty)
            {
               // MessageBox.Show("Please open an image first.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                trackbar.Value = 1;
                textbox.Text = "1";
                return false;
            }
            else
            {
                textbox.Text = ((int)trackbar.Value).ToString();
                return true;
            }
        }
        private bool TextBoxValueToTrackBar(TextBox textbox, TrackBar trackbar, int minValue, int maxValue)
        {
            if (tempPath == string.Empty)
            {
                // MessageBox.Show("Please open an image first.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                trackbar.Value = minValue;
                textbox.Text = minValue.ToString();
                return false;
            }
            else
            {
                int value;
                if (int.TryParse(textbox.Text, out value))
                {
                    // 檢查值是否在範圍內
                    value = Math.Max(minValue, Math.Min(maxValue, value));

                    // 設定 TrackBar 的值
                    trackbar.Value = value;
                    return true;
                }
                else
                {
                    // 轉換失敗，顯示錯誤訊息或採取其他適當的處理方式
                    // MessageBox.Show("Invalid value. Please enter a valid number.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return false;
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            TogglePanelVisibility(button1, panel2);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            TogglePanelVisibility(button2, panel4);
        }
        private void button3_Click(object sender, EventArgs e)
        {
            TogglePanelVisibility(button3, panel3);
            
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            if (textBox1.Text != string.Empty)
            {

                TextBoxValueToTrackBar(textBox1, trackBar1, 0, 10);
                trackBar1_Scroll(this, EventArgs.Empty);
            }

        }
        
        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            if (TrackBarValueToText(trackBar1, textBox1))
            {
                if (textBox1.Text != string.Empty)
                {

                    TextBoxValueToTrackBar(textBox1, trackBar1, 0, 10);
                    BrightNum = int.Parse(textBox1.Text);
                    UploadImageChange(pictureBox1);

                }
            }
            else
            {
                trackBar1.Value = 1;
            }
        }

        private void trackBar8_Scroll(object sender, EventArgs e)
        {
            if (TrackBarValueToText(trackRed, textBoxRed))
            {
                if (textBoxRed.Text != string.Empty)
                {

                    TextBoxValueToTrackBar(textBoxRed, trackRed, 0, 10);
                    RedNum = int.Parse(textBoxRed.Text);
                    UploadImageChange(pictureBox1);

                }
            }
            else
            {
                trackRed.Value = 1;
            }
        }

        private void trackBar7_Scroll(object sender, EventArgs e)
        {
            if (TrackBarValueToText(trackGreen, textBoxGreen))
            {
                if (textBoxGreen.Text != string.Empty)
                {

                    TextBoxValueToTrackBar(textBoxGreen, trackGreen, 0, 10);
                    GreenNum = int.Parse(textBoxGreen.Text);
                    UploadImageChange(pictureBox1);

                }
            }
            else
            {
                trackGreen.Value = 1;
            }
        }

        private void trackBar6_Scroll(object sender, EventArgs e)
        {
            if (TrackBarValueToText(trackBlue, textBoxBlue))
            {

                if (textBoxGreen.Text != string.Empty)
                {

                    TextBoxValueToTrackBar(textBoxBlue, trackBlue, 0, 10);
                    BlueNum = int.Parse(textBoxBlue.Text);
                    UploadImageChange(pictureBox1);

                }
                
            }
            else
            {
                trackBlue.Value = 1;
            }
        }

        private void panel2_Paint(object sender, PaintEventArgs e)
        {

        }

        private void bigButton_Click()
        {

        }
        private void LeftButton_Click(object sender, EventArgs e)
        {
            AngleNum += 10;
            AngleNumLabel.Text = AngleNum.ToString();
            UploadImageChange(pictureBox1);
        }
        private void RightButton_Click(object sender, EventArgs e)
        {
            AngleNum -= 10;
            AngleNumLabel.Text = AngleNum.ToString();
            UploadImageChange(pictureBox1);
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void reSetAllSet()
        {
            File.Copy(inputPath, tempPath, true);
            BrightNum = 1;
            RedNum = 1;
            GreenNum = 1;
            BlueNum = 1;
            AngleNum = 0;
            SizeNum = 100;
            NegativeBool = false;
            GrayScaleBool = false;
            MosaicBool = false;
            SharpenBool = false;
            BlurBool = false;
            ResetBarText(trackRed, textBoxRed);
            ResetBarText(trackGreen, textBoxGreen);
            ResetBarText(trackBlue, textBoxBlue);
            ResetBarText(trackBar1, textBox1);
            setPicBox();
            UpdateImage(inputPath, pictureBox1);
        }
        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            reSetAllSet();
        }

        private void SmallButton_Click(object sender, EventArgs e)
        {
            SizeNum -= 10;
            SizeNumLabel.Text = SizeNum.ToString();
            UploadImageChange(pictureBox1);
        }

        private void BigButton_Click(object sender, EventArgs e)
        {
            SizeNum += 10;
            SizeNumLabel.Text = SizeNum.ToString();
            UploadImageChange(pictureBox1);
        }
        private void pictureBox2_Click(object sender, EventArgs e)
        {
            NegativeBool = !NegativeBool;
            UploadImageChange(pictureBox1);
            setPicBox();
        }
        private void setPicBox()
        {
            NegativeBool = !NegativeBool;
            UploadImageChange(NegativePicBox);
            NegativeBool = !NegativeBool;
            GrayScaleBool = !GrayScaleBool;
            UploadImageChange(GrayScalepictureBox);
            GrayScaleBool = !GrayScaleBool;
            MosaicBool = !MosaicBool;
            UploadImageChange(MosaicPictureBox);
            MosaicBool = !MosaicBool;
            SharpenBool = !SharpenBool;
            UploadImageChange(SharpenPictureBox);
            SharpenBool = !SharpenBool;
            BlurBool = !BlurBool;
            UploadImageChange(BlurIPictureBox);
            BlurBool = !BlurBool;

        }

        private void GrayScalepictureBox_Click(object sender, EventArgs e)
        {
            GrayScaleBool = !GrayScaleBool;
            UploadImageChange(pictureBox1);
            setPicBox();
        }

        private void MosaicPictureBox_Click(object sender, EventArgs e)
        {
            MosaicBool =  !MosaicBool;
            UploadImageChange(pictureBox1);
            setPicBox();
        }

        private void SharpenPictureBox_Click(object sender, EventArgs e)
        {
            SharpenBool = !SharpenBool;
            UploadImageChange(pictureBox1);
            setPicBox();
        }

        private void BlurIPictureBox_Click(object sender, EventArgs e)
        {
            BlurBool = !BlurBool;
            UploadImageChange(pictureBox1);
            setPicBox();
        }

        private void GamaAdd_Click(object sender, EventArgs e)
        {
            GammaNum += 0.1;
            GamaNumLabel.Text = Math.Round(GammaNum, 1).ToString();
            UploadImageChange(pictureBox1);
        }

        private void GamaSub_Click(object sender, EventArgs e)
        {
            GammaNum -= 0.1;
            GamaNumLabel.Text = Math.Round(GammaNum, 1).ToString();
            UploadImageChange(pictureBox1);
        }

        private void label10_Click(object sender, EventArgs e)
        {

        }

        private void toolStripButton3_Click(object sender, EventArgs e)
        {

        }

        private void 簡體中文ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Text = "简易版图像程式";
            button1.Text = "色彩";
            button2.Text = "缩放旋转";
            button3.Text = "特殊效果";
            label3.Text = "负片";
            label4.Text = "诙谐";
            label5.Text = "马赛克";
            label6.Text = "线条";
            label9.Text = "模糊";
            label1.Text = "亮度";
            label8.Text = "红色";
            label7.Text = "绿色";
            label2.Text = "蓝色";
            sizeLable.Text = "缩放";
            angleLabel.Text = "角度";
            LeftButton.Text = "向左转";
            RightButton.Text = " 向右转";
            SmallButton.Text = " 缩小";
            BigButton.Text = "放大";
        }

        private void 繁體中文ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Text = "簡易版圖像程式";
            button1.Text = "色彩";
            button2.Text = "縮放旋轉";
            button3.Text = "特殊效果";
            label3.Text = "負片";
            label4.Text = "詼諧";
            label5.Text = "馬賽克";
            label6.Text = "線條";
            label9.Text = "模糊";
            label1.Text = "亮度";
            label8.Text = "紅色";
            label7.Text = "綠色";
            label2.Text = "藍色";
            sizeLable.Text = "縮放";
            angleLabel.Text = "角度";
            LeftButton.Text = "向左轉";
            RightButton.Text = " 向右轉";
            SmallButton.Text = " 縮小";
            BigButton.Text = "放大";

        }

        private void englishToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Text = "Simple version of image program";
            button1.Text = "Color";
            button2.Text = "Scale and rotate";
            button3.Text = "Special Effects";
            label3.Text = "Negative";
            label4.Text = "humorous";
            label5.Text = "Mosaic";
            label6.Text = "Line";
            label9.Text = "Blurred";
            label1.Text = "Brightness";
            label8.Text = "Red";
            label7.Text = "Green";
            label2.Text = "Blue";
            sizeLable.Text = "Zoom";
            angleLabel.Text = "angle";
            LeftButton.Text = "Turn left";
            RightButton.Text = "Turn right";
            SmallButton.Text = "Shrink";
            BigButton.Text = "Zoom in";
        }

        private void españolToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Text = "Versión simple del programa de imágenes";
            button1.Text = "Color";
            button2.Text = "Escalar y rotar";
            button3.Text = "Efectos especiales";
            label3.Text = "Negativo";
            label4.Text = "humorístico";
            label5.Text = "Mosaico";
            label6.Text = "Línea";
            label9.Text = "borroso";
            label1.Text = "Brillo";
            label8.Text = "Rojo";
            label7.Text = "Verde";
            label2.Text = "Azul";
            sizeLable.Text = "Zoom";
            angleLabel.Text = "ángulo";
            LeftButton.Text = "Girar a la izquierda";
            RightButton.Text = "Gira a la derecha";
            SmallButton.Text = "Reducir";
            BigButton.Text = "Acercar";
        }

        private void عربيToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Text = "نسخة بسيطة من برنامج الصور";
            button1.Text = "اللون";
            button2.Text = "تحجيم وتدوير";
            button3.Text = "المؤثرات الخاصة";
            label3.Text = "سلبي";
            label4.Text = "روح الدعابة";
            label5.Text = "فسيفساء";
            label6.Text = "خط";
            label9.Text = "غير واضح";
            label1.Text = "السطوع";
            label8.Text = "أحمر";
            label7.Text = "أخضر";
            label2.Text = "أزرق";
            sizeLable.Text = "تكبير/تصغير";
            angleLabel.Text = "angle";
            LeftButton.Text = "اتجه إلى اليسار";
            RightButton.Text = "انعطف يمينًا";
            SmallButton.Text = "تقليص";
            BigButton.Text = "تكبير";
        }

        private void แบบไทยToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Text = "โปรแกรมรูปภาพเวอร์ชันธรรมดา";
            button1.Text = "สี";
            button2.Text = "ปรับขนาดและหมุน";
            button3.Text = "เอฟเฟกต์พิเศษ";
            label3.Text = "เชิงลบ";
            label4.Text = "ตลก";
            label5.Text = "โมเสค";
            label6.Text = "เส้น";
            label9.Text = "เบลอ";
            label1.Text = "ความสว่าง";
            label8.Text = "สีแดง";
            label7.Text = "สีเขียว";
            label2.Text = "สีน้ำเงิน";
            sizeLable.Text = "ซูม";
            angleLabel.Text = "มุม";
            LeftButton.Text = "เลี้ยวซ้าย";
            RightButton.Text = "เลี้ยวขวา";
            SmallButton.Text = "ลดขนาด";
            BigButton.Text = "ขยาย";
        }

        private void françaisToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Text = "Version simple du programme d'image";
            button1.Text = "Couleur";
            button2.Text = "Mettre à l'échelle et faire pivoter";
            button3.Text = "Effets spéciaux";
            label3.Text = "Négatif";
            label4.Text = "humoristique";
            label5.Text = "Mosaïque";
            label6.Text = "Ligne";
            label9.Text = "Flou";
            label1.Text = "Luminosité";
            label8.Text = "Rouge";
            label7.Text = "Vert";
            label2.Text = "Bleu";
            sizeLable.Text = "Zoom";
            angleLabel.Text = "angle";
            LeftButton.Text = "Tourner à gauche";
            RightButton.Text = "Tourner à droite";
            SmallButton.Text = "Réduire";
            BigButton.Text = "Zoom avant";
        }

        private void 日文ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Text = "画像プログラムの簡易版";
            button1.Text = "色";
            button2.Text = "スケールと回転";
            button3.Text = "特殊効果";
            label3.Text = "ネガティブ";
            label4.Text = "ユーモラス";
            label5.Text = "モザイク";
            label6.Text = "行";
            label9.Text = "ぼやけた";
            label1.Text = "明るさ";
            label8.Text = "赤";
            label7.Text = "緑";
            label2.Text = "青";
            sizeLable.Text = "ズーム";
            angleLabel.Text = "角度";
            LeftButton.Text = "左折";
            RightButton.Text = "右折";
            SmallButton.Text = "縮小";
            BigButton.Text = "ズームイン";
        }

        private void 한국어ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Text = "간단한 이미지 프로그램 버전";
            button1.Text = "색상";
            button2.Text = "크기 조정 및 회전";
            button3.Text = "특수 효과";
            label3.Text = "부정";
            label4.Text = "유머러스함";
            label5.Text = "모자이크";
            label6.Text = "선";
            label9.Text = "흐릿함";
            label1.Text = "밝기";
            label8.Text = "빨간색";
            label7.Text = "녹색";
            label2.Text = "파란색";
            sizeLable.Text = "확대/축소";
            angleLabel.Text = "각도";
            LeftButton.Text = "좌회전";
            RightButton.Text = "우회전";
            SmallButton.Text = "축소";
            BigButton.Text = "확대";
        }

        private void русскийToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Text = "Простая версия программы обработки изображений";
            button1.Text = "Цвет";
            button2.Text = "Масштабировать и вращать";
            button3.Text = "Специальные эффекты";
            label3.Text = "Отрицательный";
            label4.Text = "юмористический";
            label5.Text = "Мозаика";
            label6.Text = "Линия";
            label9.Text = "Размыто";
            label1.Text = "Яркость";
            label8.Text = "Красный";
            label7.Text = "Зеленый";
            label2.Text = "Синий";
            sizeLable.Text = "Масштаб";
            angleLabel.Text = "угол";
            LeftButton.Text = "Поверните налево";
            RightButton.Text = "Поверните направо";
            SmallButton.Text = "Сжать";
            BigButton.Text = "Увеличить масштаб";
        }

        private void deutschToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Text = "Einfache Version des Bildprogramms";
            button1.Text = "Farbe";
            button2.Text = "Skalieren und drehen";
            button3.Text = "Spezialeffekte";
            label3.Text = "Negativ";
            label4.Text = "humorvoll";
            label5.Text = "Mosaik";
            label6.Text = "Zeile";
            label9.Text = "Unscharf";
            label1.Text = "Helligkeit";
            label8.Text = "Rot";
            label7.Text = "Grün";
            label2.Text = "Blau";
            sizeLable.Text = "Zoom";
            angleLabel.Text = "angle";
            LeftButton.Text = "Links abbiegen";
            RightButton.Text = "Rechts abbiegen";
            SmallButton.Text = "Shrink";
            BigButton.Text = "Heranzoomen";
        }

        private void italianoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Text = "Versione semplice del programma immagine";
            button1.Text = "Colore";
            button2.Text = "Scala e ruota";
            button3.Text = "Effetti speciali";
            label3.Text = "Negativo";
            label4.Text = "divertente";
            label5.Text = "Mosaico";
            label6.Text = "Linea";
            label9.Text = "Sfocato";
            label1.Text = "Luminosità";
            label8.Text = "Rosso";
            label7.Text = "Verde";
            label2.Text = "Blu";
            sizeLable.Text = "Zoom";
            angleLabel.Text = "angolo";
            LeftButton.Text = "Gira a sinistra";
            RightButton.Text = "Gira a destra";
            SmallButton.Text = "Riduci";
            BigButton.Text = "Ingrandisci";
        }

        private void tiếngViệtToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Text = "Phiên bản đơn giản của chương trình hình ảnh";
            button1.Text = "Màu";
            button2.Text = "Chia tỷ lệ và xoay";
            button3.Text = "Hiệu ứng đặc biệt";
            label3.Text = "Phủ định";
            label4.Text = "hài hước";
            label5.Text = "Khảm";
            label6.Text = "Dòng";
            label9.Text = "Mờ";
            label1.Text = "Độ sáng";
            label8.Text = "Đỏ";
            label7.Text = "Xanh";
            label2.Text = "Xanh";
            sizeLable.Text = "Thu phóng";
            angleLabel.Text = "góc";
            LeftButton.Text = "Rẽ trái";
            RightButton.Text = "Rẽ phải";
            SmallButton.Text = "Thu nhỏ";
            BigButton.Text = "Phóng to";
        }

        private void Langue_ButtonClick(object sender, EventArgs e)
        {

        }
    }
}
