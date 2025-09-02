#include <pjsr/Sizer.jsh>

function ImageViewer(parent)
{
    this.__base__ = Control;
    this.__base__(parent);

    this.canPaint = true;
    this.canUpdate = true;

    this.image = null;
    this.setMinSize(300, 300);


    this.loadImage = function(path)
    {
        if (File.exists(path))
        {
            try
            {
                this.image = new Bitmap(path);
                this.minWidth = this.image.width;
                this.minHeight = this.image.height;
                this.update();
            }
            catch (e)
            {
                console.criticalln("Nie udało się załadować obrazu: " + e.message);
            }
        }
    };

    this.onPaint = function(x0, y0, x1, y1)
    {
        console.writeln('Rysowanie ImageViewer '+x0+' '+y0+' '+x1+' '+y1);
        let g = new Graphics(this);

        if (this.image)
        {
            g.drawBitmap(0, 0, this.image);
        }
        else
        {
            console.writeln("Brak obrazu do wyświetlenia");
            g.fillRect(x0, y0, x1, y1, new Brush(0xFF404040));
            g.pen = new Pen(0xFF000000);
            g.drawRect(x0, y0, x1 - 1, y1 - 1);
        }

        g.end();
    };
}

ImageViewer.prototype = Object.create(Control.prototype);


function SunDialog() 
{
    this.__base__ = Dialog;
    this.__base__();

    this.windowTitle = "SDO Sun Viewer";
    this.minWidth = 800;
    this.minHeight = 300;


    // this.viewList = new ViewList(this);
    // this.viewList.label = "Wybierz widok docelowy";
    // this.viewList.getMainViews();
    // this.sizer = new VerticalSizer;
    // this.sizer.add(this.viewList);
   
    var imagesSizer = new HorizontalSizer;

    var img1 = new ImageViewer(this);
    var img2 = new ImageViewer(this);

    imagesSizer.add(img1);
    imagesSizer.add(img2);
    imagesSizer.spacing = 10;
    imagesSizer.margin = 10;


    

    var btnOK = new PushButton(this);
    btnOK.text = "OK";
    btnOK.icon = this.scaledResource(":/icons/ok.png"); 


    var mainSizer = new VerticalSizer;

    mainSizer.add(imagesSizer);
    mainSizer.add(btnOK);

    this.sizer = mainSizer;

}

SunDialog.prototype = new Dialog;


function showDialog() {
    let dialog = new SunDialog();
    return dialog.execute();
}