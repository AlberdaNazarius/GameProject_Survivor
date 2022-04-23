# Instruction to UI

## Inherit system:

UI -> Button; UI -> Container

Container -> Panel

## UI (class) description:

UI (class) is super class of all ui elements

### Properties:

Vector2f relPosition - assigns a relative position relative to the father

bool isVisible - is this UI element visible by default

bool isActive - is this UI element active

### Methods:

#### Constructors (3 overloaded):

UI(Vector2f pos, bool isVis);

UI(Vector2f pos);

UI();

#### Deconstuctor:

virtual ~UI();

#### Other methods:

void setPosition(Vector2f pos); - set relative position (relPosition)

virtual void setVisible(bool isVis); - set visibility (isVisible)

bool getVisible(); - get visibility (isVisible)

virtual void setActive(bool isAct); - set activity (isActive)

virtual void render(RenderTarget& target, Vector2f offset) = 0; - render ui this element

## Button description:

Button is common ui element that trigger function when pressed

### Properties:

Sprite sprite - texture with coords and bounds

Texture* idle; - texture when idle

Texture* clicked; - texture when clicked

Texture* hover; - texture when hovering mouse over this button

Font* font; - text font

Text text; - text in centre of button

T Action; - function that called when mouse clicked

### Methods:

#### Constructors:

Button(Vector2f pos, IntRect intRect, std::string text); 

#### Deconstuctor:

~Button();

#### Other methods:

void setSize(IntRect intRect); - set texture rect sizes

void setTexture(Texture* idle, Texture* clicked); - set sprite texture

void setFont(Font* font); - set text font

void setDelegate(T func); - set function that will be called after click

void update(Vector2f pos); - update texture of button

bool checkClick(Vector2f pos); - check if button was clicked

void render(RenderTarget& target, Vector2f offset); - render button sprite and text

## Container description:

Container is basic ui element that can content other ui elements

Parent - ui element that contain other element, child - ui element that is contained in other element

Rendering location of child depends offset of parent + relative position of child

### Properties:

std::vector<UI*> childs; - vector of childs

### Methods:

#### Deconstuctor:

virtual ~Container();

#### Other methods:

void render(RenderTarget& target, Vector2f offset); - render all childrens

void setVisible(bool isVis); - set isVisible Container and set isActive of childrens

void setActive(bool isAct); - set isActive of childrens

void addChild(UI* child); - add new children

void removeChild(UI* child); - remove existing child (search for element with same address)

## Panel description:

Basically container but with sprite

### Properties:

Sprite sprite;

### Methods:

#### Constructors:

Panel(Texture* texture, Vector2f pos, IntRect intRect);

Panel(Vector2f pos, IntRect intRect);
  
Panel();

#### Other methods:

void setTexture(Texture* texture); - set sprite texture

void setSize(IntRect intRect); - set sprite texture rect

void render(RenderTarget& target, Vector2f offset); - render Panel and childs
