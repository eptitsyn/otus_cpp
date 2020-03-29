#include "shapes.hpp"

#include <iostream>
#include <memory>
#include <vector>

using Document = std::vector<std::unique_ptr<IShape>>;

/**
 * @brief View. Занимается отображением данных.
 */
class View {
public:
    void ClearCanvas() const{};
    void Draw(const std::shared_ptr<Document> document) const{
        ClearCanvas();
        for(auto &i : *document){
            i->Draw();
        }
    };
};

class Controller;

/**
 * @brief Model. Занимается хранением данных.
 */
class Model {
public:
    Model() : document(std::make_shared<Document>()) {};
    void ClearDocument(){ 
        document->clear();
        Refresh();
    }
    void setDocument(std::shared_ptr<Document> doc) {
        document = doc;
        Refresh();
    };
    const std::shared_ptr<Document> getDocument() const{
        return document;
    };
    void AddObject(std::unique_ptr<IShape> object){
        document->push_back(move(object));
        Refresh();
    }
    void setController(Controller &controller);
    void Refresh();

private:
    std::shared_ptr<Document> document;
    Controller* controller;
};

/**
 * @brief Контроллер.
 */
class Controller{
public:
    Controller(Model &model, const View &view) : model(&model), view(&view){};

    void CreateNewDocument(){
        model->ClearDocument();
    };
    void ImportDocumentFromFile(std::string &filename){
        auto doc = std::make_shared<Document>();
        model->setDocument(doc);
    };
    void ExportDocumentToFile(std::string &filename){
        model->getDocument();
    };
    void AddShape(std::unique_ptr<IShape> shape){
        model->AddObject(move(shape));
    };
    void RemoveShape(){

    };
    void Refresh(){
        view->Draw(model->getDocument());
    }
private:
    Model* model;
    const View* view;
};

void Model::setController(Controller &controller_){
    controller = &controller_;
}
void Model::Refresh(){
    controller->Refresh();
}

int main (int argc, char *argv[]){
    View view;
    Model model;
    Controller controller(model, view);
    model.setController(controller);

    controller.CreateNewDocument();
    controller.AddShape(std::make_unique<Circle>(10, 20, 10));
    controller.AddShape(std::make_unique<Square>(10, 10, 5));

    return 0;
}