package cs2410.assn4;

import javafx.scene.control.TextInputDialog;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.stage.Stage;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Optional;
import java.util.Scanner;

/**
 * The controller/program logic for SUPER TURNT IMAGE VIEWER
 * @author Jack Kiefer
 * @version 1.0
 */

class Controller {
    /**
     * True if there's no images in the list.
     */
    boolean noImages = false;

    /**
     * The current image index
     */
    private int curImage = 0;

    /**
     * The images stored as Images
     */
    private ArrayList<Image> list = new ArrayList<>();

    /**
     * The urls for the images. The url at index n corresponds to the image at index n in the other ArrayList
     */
    private ArrayList<String> urls = new ArrayList<>();

    /**
     * A file that is a list of URLs
     */
    private String filename = "data/images";

    /**
     * Reads in the list of URLs
     */
    void init()
    {
        Scanner fileInput = null;

        try {
            fileInput = new Scanner(new FileReader(filename));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        String url;

        while (fileInput.hasNext()) {
            url = fileInput.nextLine();
            urls.add(url);
            list.add(new Image(url));
        }

    }

    /**
     * Required for a bit of logic in the Viewer class
     * @return true if the list has more than one image
     */
    boolean moreThanOneImage()
    {
        return list.size() > 1;
    }

    /**
     * Retrieves the next image in the list
     * @return the next image
     */
    Image getNextImage()
    {
        ++curImage;
        if (curImage > list.size() - 1)
        {
            curImage = 0;
        }
        return list.get(curImage);
    }

    /**
     * Retrieves the previous image in the list
     * @return the previous image
     */
    Image getPrevImage()
    {
        --curImage;
        if (curImage < 0)
        {
            curImage = list.size() - 1;
        }
        return list.get(curImage);
    }

    /**
     * Deletes the current image from the list, and shows a Kermit notice if no images remain
     */
    void deleteCur()
    {
        if (list.size() > 1)
        {
            list.remove(curImage);
            urls.remove(curImage);
            --curImage;
            if (curImage < 0) curImage = 0;
        }
        else
        {
            list.add(new Image("http://i2.kym-cdn.com/photos/images/original/000/610/080/867.png"));
            list.remove(curImage);
            urls.remove(curImage);
            curImage = 0;
            noImages = true;
        }
    }

    /**
     * Gets current image
     * @return ...the current image. Javadocs, please!
     */
    Image getCurImage()
    {
        return list.get(curImage);
    }

    /**
     * Adds an image to the list
     * @return The new image that has been added
     */
    Image newImage()
    {
        String input = null;
        TextInputDialog getOption = new TextInputDialog("");
        getOption.setTitle("ADD A TURNT IMAGE");
        getOption.setHeaderText(null);
        getOption.setContentText("Image URL: ");
        getOption.setGraphic(new ImageView(this.getClass().getResource("resources/info.png").toString()));
        Stage stage1 = (Stage) getOption.getDialogPane().getScene().getWindow();
        stage1.getIcons().add(new Image(this.getClass().getResource("resources/info.png").toString()));

        Optional<String> result = getOption.showAndWait();

        if (result.isPresent()) {
            input = result.get();
        }

        Image newImage = new Image(input);

        if (noImages)
        {
            list.remove(0);
            curImage = -1;
        }

        ++curImage;
        list.add(curImage, newImage);
        urls.add(curImage, input);

        noImages = false;

        return list.get(curImage);
    }

    /**
     * Writes the current list of URLs to a file prior to closing the program
     */
    void save()
    {
        PrintWriter writer = null;

        try {
            writer = new PrintWriter(new FileOutputStream(filename, false));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        for( String s : urls) {
            writer.println(s);
        }

        writer.close();
    }

}
