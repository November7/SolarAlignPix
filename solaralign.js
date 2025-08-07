// #feature-id    SolarUtilities > Solar Align

// var imageUrl = "https://sdo.gsfc.nasa.gov/assets/img/browse/2025/05/02/20250502_000000_1024_HMIIC.jpg";


// let localPath = File.systemTempDirectory + "/sun_image.jpg";

// function main()
// {


//     let T = new NetworkTransfer;
//     T.setURL( imageUrl);

//     let data = new ByteArray;
//     T.onDownloadDataAvailable = function( moreData )
//     {
//         data.add( moreData );
//         return true;
//     };

//     if ( !T.download() )
//         throw new Error( T.errorInformation );


//    File.writeFile( localPath, data );


//    let imageWindows = ImageWindow.open(localPath);
//    if (imageWindows.length > 0) 
//     {
//       imageWindows[0].show();
//    } else
//      {
//       console.writeln("Failed to open image.");
//    }

// }

// main();
#feature-id    SolarUtilities > Solar Align

// Import modułów PJSR
#include <pjsr/Sizer.jsh>
#include <pjsr/StdButton.jsh>
#include <pjsr/StdDialogCode.jsh>
#include <pjsr/FrameStyle.jsh>

// URL obrazu Słońca
var imageUrl = "https://sdo.gsfc.nasa.gov/assets/img/browse/2025/05/02/20250502_000000_1024_HMIIC.jpg";
var localPath = File.systemTempDirectory + "/sun_image.jpg";

// Funkcja pobierania obrazu
function downloadImage() {
   try {
      console.writeln("Pobieranie obrazu: " + imageUrl);
      let T = new NetworkTransfer;
      T.setURL(imageUrl);

      let data = new ByteArray;
      T.onDownloadDataAvailable = function(moreData) {
         data.add(moreData);
         return true;
      };

      if (!T.download())
         throw new Error(T.errorInformation);

      File.writeFile(localPath, data);
      console.writeln("Zapisano: " + localPath);
      return true;
   }
   catch (err) {
      console.criticalln("Błąd: " + err.message);
      return false;
   }
}

function ImageViewer(path) {
   this.__base__ = Control;
   this.__base__();

   this.image = null;

   if (File.exists(path)) {
      try {
         this.image = new Bitmap(path);
         this.setFixedSize(this.image.width, this.image.height);
      } catch (e) {
         console.criticalln("Nie udało się załadować obrazu: " + e.message);
      }
   }

   this.onPaint = function(x0, y0, x1, y1) {
      if (this.image) {
         let g = new Graphics(this);
         g.drawBitmap(0, 0, this.image);
         g.end();
      }
   };
}

ImageViewer.prototype = new Control;

// Klasa dialogu
function MyDialog() {
   this.__base__ = Dialog;
   this.__base__();

   this.image_Viewer = null;

   this.download_Button = new PushButton(this);
   this.download_Button.text = "Pobierz i pokaż obraz";
   this.download_Button.onClick = function() {
      if (downloadImage()) {
         if (this.dialog.image_Viewer)
            this.dialog.sizer.remove(this.dialog.image_Viewer);

         this.dialog.image_Viewer = new ImageViewer(localPath);
         this.dialog.sizer.insert(0, this.dialog.image_Viewer);
         this.dialog.adjustToContents();
      }
   };

   // Układ
   this.sizer = new VerticalSizer;
   this.sizer.margin = 10;
   this.sizer.spacing = 6;
   this.sizer.add(this.download_Button);

   this.windowTitle = "SDO Sun Viewer";
   this.adjustToContents();
}

MyDialog.prototype = new Dialog;

var dialog = new MyDialog();
dialog.execute();
