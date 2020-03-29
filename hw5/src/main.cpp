#include "shapes.hpp"

#include <iostream>
#include <memory>
#include <vector>

using Document = std::vector<std::unique_ptr<IShape>>;


/**
 * @brief Индекс первой с когца фигуры в которой лежит точка
 */
int pointInFigure(const std::shared_ptr<Document> figs, int x, int y){
    //не реверс итератор, потому что его сложно превратить обратно в forward_iterator;
    auto p = figs.get();
    for(int i = p->size()-1; i!=0; --i){
        if (p->at(i)->pointInside(x,y)) { return i; };
    }
    return -1;
}

/**
 * @brief View. Занимается отображением данных.
 */
class View {
public:
    void ClearCanvas() const{
        //очистить холст
        std::cout << "=== Clear canvas ===\n";
    };
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
    void AddObject(std::unique_ptr<IShape> &&object){
        document->push_back(move(object));
        Refresh();
    }
    void RemoveObject(size_t index){
        document->erase(document->begin()+index);
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
    //!Constructor
    Controller(Model &model, const View &view) : model(&model), view(&view){};

    //!Create new document
    void CreateNewDocument(){
        model->ClearDocument();
    };

    
    void ImportDocumentFromFile(const std::string &&filename){
        std::cout << "Import from " << filename << "\n";
        auto deserialized = std::make_shared<Document>();
        model->setDocument(deserialized);
    };
    void ExportDocumentToFile(const std::string &&filename){
        model->getDocument();
        std::cout << "Export to " << filename << "\n";
        //serialize(model->getDocument);
    };
    //!Add shape to canvas
    void AddShape(std::unique_ptr<IShape> shape){
        model->AddObject(move(shape));
    };

    //!remove shape from canvas
    void RemoveShape(int x, int y){
        int i = pointInFigure(model->getDocument(), x, y);
        if(i != -1 && i < static_cast<int>(model->getDocument()->size())){
            model->RemoveObject(i); 
        }
        
    };

    //!refresh canvas
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



int main (){
    View view;
    Model model;
    Controller controller(model, view);
    model.setController(controller);

    controller.CreateNewDocument();
    controller.AddShape(std::make_unique<Circle>(10, 20, 10));
    controller.AddShape(std::make_unique<Square>(10, 10, 5));
    controller.ExportDocumentToFile("test.bin");

    return 0;
}