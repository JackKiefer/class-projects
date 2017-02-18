package cs2410.assn4;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.image.ImageView;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;
import javafx.scene.control.Button;
import javafx.stage.WindowEvent;

/**
 * The GUI/Viewer for SUPER TURNT IMAGE VIEWER
 *
 * @author Jack Kiefer
 * @version 1.0
 */
public class Viewer extends Application{
    /**
     * Go to previous image
     */
    private Button prev = new Button("Prev");

    /**
     * Go to next image
     */
    private Button next = new Button("Next");

    /**
     * Delete image
     */
    private Button del = new Button("Del");

    /**
     * Add Image
     */
    private Button add = new Button("Add");

    /**
     * Handles buttons
     */
    private EventHandler<ActionEvent> handler;

    /**
     * Handles closeRequest
     */
    private EventHandler<WindowEvent> handleClose;

    /**
     * Views turnt images
     */
    private ImageView view1 = new ImageView();

    /**
     * Controls logic of the program
     */
    private Controller ctlr = new Controller();

    /**
     * Starts the GUI
     * @param primaryStage the main GUI stage
     */
    @Override
    public void start(Stage primaryStage) {
        Pane pane1 = new Pane(prev, next, del, add);
        Scene scene1 = new Scene(pane1, 500, 600);
        primaryStage.setScene(scene1);

        initHandler();
        ctlr.init();

        primaryStage.setTitle("✧ʕ̢̣̣̣̣̩̩̩̩·͡˔·ོɁ̡̣̣̣̣̩̩̩̩✧ SUPER TURNT IMAGE VIEWER");
        primaryStage.setResizable(false);
        primaryStage.setOnCloseRequest(handleClose);

        prev.setOnAction(handler);
        prev.setPrefSize(125,100);
        prev.setLayoutX(0);
        prev.setLayoutY(500);

        del.setOnAction(handler);
        del.setPrefSize(125,100);
        del.setLayoutX(125);
        del.setLayoutY(500);

        add.setOnAction(handler);
        add.setPrefSize(125,100);
        add.setLayoutX(250);
        add.setLayoutY(500);

        next.setOnAction(handler);
        next.setPrefSize(125,100);
        next.setLayoutX(375);
        next.setLayoutY(500);

        view1.setPreserveRatio(true);
        view1.setFitWidth(500);
        view1.setFitHeight(500);

        view1.setImage(ctlr.getCurImage());

        pane1.getChildren().add(view1);

        primaryStage.show();
    }

    /**
     * Initializes handlers
     */
    private void initHandler() {
        handleClose = new EventHandler<WindowEvent>() {
            @Override
            public void handle(WindowEvent event) {
               ctlr.save();
            }
        };
        handler = new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                Object source = event.getSource();

                if(source == next) {
                    view1.setImage(ctlr.getNextImage());
                }
                else if(source == prev) {
                    view1.setImage(ctlr.getPrevImage());
                }
                else if(source == add) {
                    view1.setImage(ctlr.newImage());
                    if (ctlr.moreThanOneImage())
                    {
                        next.setDisable(false);
                        prev.setDisable(false);
                    }

                    del.setDisable(false);

                }
                else if(source == del) {
                    ctlr.deleteCur();
                    view1.setImage(ctlr.getCurImage());

                    if (!ctlr.moreThanOneImage())
                    {
                        next.setDisable(true);
                        prev.setDisable(true);
                    }

                    if (ctlr.noImages)
                    {
                       del.setDisable(true);
                    }
                }
            }
        };
    }
}