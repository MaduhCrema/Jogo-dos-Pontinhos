// Inicializando Variaveis

var DOT_RADIUS = 6;
var DOT_DIAMETER = DOT_RADIUS * 2;
var DOT_SPACING = 45;
var GRID_PADDING = DOT_SPACING / 2;
var MOUSE_DISTANCE = 15;

// Variaveis Globais

let dotArray = [];
let squaresArray = [];
let linksArray = [];
let ArrayLinks = [];
let ArraySquares = [];
let origin = null;
let dotCountL = 0;
let dotCountC = 0;
let colours = { p1: null, p2: null };
let turn = "p1";
let scores = { p1: 0, p2: 0 };
let required = false;

//CLASSES//
//verifica a bolinha
function Dot(x, y, radius, gx, gy) {
  this.x = x;
  this.y = y;
  this.radius = radius;
  this.gx = gx;
  this.gy = gy;
  //desenha a bolinha branca do ponto
  this.draw = function () {
    c.beginPath();
    c.arc(this.x, this.y, this.radius, Math.PI * 2, false);
    c.fillStyle = "white";
    c.fill();
  };

  this.update = function () {
    // expande a bolinha quando passa por cima
    if (
      (mouse.x - this.x < MOUSE_DISTANCE &&
        mouse.x - this.x > -MOUSE_DISTANCE &&
        mouse.y - this.y < MOUSE_DISTANCE &&
        mouse.y - this.y > -MOUSE_DISTANCE) ||
      origin === this
    ) {
      this.radius = DOT_RADIUS * 1.5;
    } else {
      this.radius = DOT_RADIUS;
    }

    if (turn == "p1") {
      2; // Se o click for dentro da bolinha verifica se origin == null,ou seja, que não clicou na mesma bolinha
      // se for clicavel, verifica se a jogada é valida e cria o link, se não origin continua null
      if (
        click.x < this.x + this.radius &&
        click.x > this.x - this.radius &&
        click.y < this.y + this.radius &&
        click.y > this.y - this.radius
      ) {
        if (origin) {
          if (checkValidMove(this)) {
            createLink(this); // da primeia bolinha clicada ate a segunda bolinha clicada
          } else {
            origin = null;
          }
        } else {
          origin = this;
        }

        click.x = undefined; // retorna para o padrao
        click.y = undefined;

        required = false;
      }
    }
    // verifica se ta na vez do PC e faz a jogada do minimax
    while (turn == "p2" && !required) {
      //passa o array dos links pro minimax
      ArrayLinks.toString().replace(/,/g, " ");
      ArraySquares.toString().replace(/,/g, " ");
      required = server(); // chama o minimax
    }
    console.log(squaresArray);
    this.draw(); // desenha no canva o link
  };
}

// cria link
function Link(start, end) {
  // Y-X
  // dois tipos de link horizontal e vertical
  if (start.gy === end.gy) {
    // horizontal p1.y == p2.y
    if (start.gx < end.gx) {
      // se p1.x < p2,x, direção normal
      this.start = start;
      this.end = end;
    } else {
      // se p1.x > p2.x, direção ao contraria
      this.start = end;
      this.end = start;
    }
  } else {
    // vertical p1.x == p2.x
    if (start.gy < end.gy) {
      // de cima para baixo o link
      this.start = start;
      this.end = end;
    } else {
      // baixo para cima
      this.start = end;
      this.end = start;
    }
  }

  this.draw = function () {
    c.beginPath();
    c.lineWidth = 5;
    c.moveTo(this.start.x, this.start.y); //começo da linha
    c.lineTo(this.end.x, this.end.y); //fim da linha
    c.strokeStyle = "#666"; //cor branca
    c.stroke(); //desenha linha
  };
}

//desenha quadrado preenchido
function Square(startX, startY, endX, endY, colour) {
  this.sX = startX;
  this.sY = startY;
  this.eX = endX;
  this.eY = endY;
  this.colour = colour;

  updateScores(); // da ponto pro player

  this.draw = function () {
    c.fillStyle = this.colour;
    c.fillRect(this.sX, this.sY, this.eX, this.eY);
  };
}

// faz o link do momento, mesmo se n funga

function renderActiveLink() {
  c.beginPath();
  c.lineWidth = 5;
  c.shadowBlur = 0;
  c.moveTo(origin.x, origin.y);
  c.lineTo(mouse.x, mouse.y);
  c.strokeStyle = "#666";
  c.stroke();
}

//CHECA SE O MOVIMENTO É VALIDO
function checkValidMove(target) {
  // checa se o movimento ja não esta feito
  if (
    linksArray.find(
      (link) =>
        //origem e alvo
        (origin.gx === link.start.gx &&
          origin.gy === link.start.gy &&
          target.gx === link.end.gx &&
          target.gy === link.end.gy) ||
        (origin.gx === link.end.gx &&
          origin.gy === link.end.gy &&
          target.gx === link.start.gx &&
          target.gy === link.start.gy)
    )
  )
    return false;

  // não permite movimentos na diagonal
  if (
    ((origin.gx === target.gx - 1 || origin.gx === target.gx + 1) &&
      origin.gy === target.gy) || // x-movimento
    ((origin.gy === target.gy - 1 || origin.gy === target.gy + 1) &&
      origin.gx === target.gx)
  ) {
    // y-movimento
    return true;
  }

  return false;
}

//CHECA SE O MOVIMENTO É VALIDO
function checkValidMovePC(origem, target) {
  // checa se o movimento ja não esta feito
  if (
    linksArray.find(
      (link) =>
        //origem e alvo
        (origem.gx === link.start.gx &&
          origem.gy === link.start.gy &&
          target.gx === link.end.gx &&
          target.gy === link.end.gy) ||
        (origem.gx === link.end.gx &&
          origem.gy === link.end.gy &&
          target.gx === link.start.gx &&
          target.gy === link.start.gy)
    )
  )
    return false;

  // não permite movimentos na diagonal
  if (
    ((origem.gx === target.gx - 1 || origem.gx === target.gx + 1) &&
      origem.gy === target.gy) || // x-movimento
    ((origem.gy === target.gy - 1 || origem.gy === target.gy + 1) &&
      origem.gx === target.gx)
  ) {
    // y-movimento
    return true;
  }
}

function createLink(target) {
  ArrayLinks.push(origin.gy, origin.gx, target.gy, target.gx);

  var newLink = new Link(origin, target); // manda criar o novo link
  linksArray.push(newLink); // coloca o novo link de pontos no array

  let squareCount = squaresArray.length; // numero de quadrados feitos
  checkForSquare(newLink); //checa se fecha um quadrado
  origin = null; //origin volta  anull

  // muda a vez do jogador se o numero de quadrados não atualizou
  if (squareCount === squaresArray.length) {
    turn = turn === "p1" ? "p2" : "p1";
    document.querySelector("#turn").classList.toggle("p2-turn");
  }
}

function createLinkPC(origem, alvo) {
  /*objeto para passar pro array que vai atualizar as infos no minimax*/
  var link = {
    p1X: undefined,
    p1Y: undefined,
    p2X: undefined,
    p2Y: undefined,
  };

  link.p1X = origem.x;
  link.p2X = alvo.x;
  link.p1Y = origem.y;
  link.p2Y = alvo.y;

  ArrayLinks.push(link);

  var newLink = new Link(origem, alvo); // manda criar o novo link
  linksArray.push(newLink); // coloca o novo link de pontos no array

  let squareCount = squaresArray.length; // numero de quadrados feitos
  checkForSquare(newLink); //checa se fecha um quadrado
  origin = null; //origin volta  anull

  // muda a vez do jogador se o numero de quadrados não atualizou
  if (squareCount === squaresArray.length) {
    turn = turn === "p1" ? "p2" : "p1";
    document.querySelector("#turn").classList.toggle("p2-turn");
  }
}

// CHECA QUADRADOS

function checkForSquare(link) {
  // MOVIMENTO HORIZONTAL
  if (link.start.gy === link.end.gy) {
    // CHECA O TOPO DO QUADRADO
    if (link.start.gy !== 0) {
      const upperLeft = linksArray.find(
        (l) =>
          l.start.gy === link.start.gy - 1 &&
          l.end.gy === link.start.gy &&
          l.start.gx === link.start.gx
      );
      const upperTop = linksArray.find(
        (l) =>
          l.start.gx === link.start.gx &&
          l.end.gx === link.end.gx &&
          l.start.gy === link.start.gy - 1
      );
      const upperRight = linksArray.find(
        (l) =>
          l.start.gy === link.start.gy - 1 &&
          l.end.gy === link.start.gy &&
          l.start.gx === link.end.gx
      );

      if (upperLeft && upperTop && upperRight) {
        squaresArray.push(
          new Square(
            upperTop.start.x,
            upperTop.start.y,
            DOT_SPACING,
            DOT_SPACING,
            colours[turn]
          )
        );
        // passa pro arraysquares comunicar com o minimax
        if (turn == "p1") {
          ArraySquares.push(upperTop.start.x, upperTop.start.y, 1);
        }
        if (turn == "p2") {
          ArraySquares.push(upperTop.start.x, upperTop.start.y, 2);
        }
      }
    }

    // CHECA EMBAIXO DO QUADRADO
    if (link.start.gy !== dotCountC - 1) {
      const lowerLeft = linksArray.find(
        (l) =>
          l.start.gy === link.start.gy &&
          l.end.gy === link.start.gy + 1 &&
          l.start.gx === link.start.gx
      );
      const lowerBottom = linksArray.find(
        (l) =>
          l.start.gx === link.start.gx &&
          l.end.gx === link.end.gx &&
          l.start.gy === link.start.gy + 1
      );
      const lowerRight = linksArray.find(
        (l) =>
          l.start.gy === link.end.gy &&
          l.end.gy === link.end.gy + 1 &&
          l.start.gx === link.end.gx
      );

      if (lowerLeft && lowerBottom && lowerRight) {
        squaresArray.push(
          new Square(
            lowerLeft.start.x,
            lowerLeft.start.y,
            DOT_SPACING,
            DOT_SPACING,
            colours[turn]
          )
        );
        // passa pro arraysquares comunicar com o minimax
        if (turn == "p1") {
          ArraySquares.push(lowerLeft.start.x, lowerLeft.start.y, 1);
        }
        if (turn == "p2") {
          ArraySquares.push(lowerLeft.start.x, lowerLeft.start.y, 2);
        }
      }
    }
  }
  // MOVIMENTO VERTICAL
  else {
    // CECHA LADO ESQUERDOD O QUADRADO
    if (link.start.gx !== 0) {
      const leftTop = linksArray.find(
        (l) =>
          l.start.gx === link.start.gx - 1 &&
          l.end.gx === link.start.gx &&
          l.start.gy === link.start.gy
      );
      const leftLeft = linksArray.find(
        (l) =>
          l.start.gy === link.start.gy &&
          l.end.gy === link.end.gy &&
          l.start.gx === link.start.gx - 1
      );
      const leftBottom = linksArray.find(
        (l) =>
          l.start.gx === link.end.gx - 1 &&
          l.end.gx === link.end.gx &&
          l.start.gy === link.end.gy
      );

      if (leftTop && leftLeft && leftBottom) {
        squaresArray.push(
          new Square(
            leftTop.start.x,
            leftTop.start.y,
            DOT_SPACING,
            DOT_SPACING,
            colours[turn]
          )
        );
        // passa pro arraysquares comunicar com o minimax
        if (turn == "p1") {
          ArraySquares.push(leftTop.start.x, leftTop.start.y, 1);
        }
        if (turn == "p2") {
          ArraySquares.push(leftTop.start.x, leftTop.start.y, 2);
        }
      }
    }

    // CHECA LADO DIREITO DO QUADRADO
    if (link.start.gx !== dotCountC - 1) {
      const rightTop = linksArray.find(
        (l) =>
          l.start.gx === link.start.gx &&
          l.end.gx === link.start.gx + 1 &&
          l.start.gy === link.start.gy
      );
      const rightRight = linksArray.find(
        (l) =>
          l.start.gy === link.start.gy &&
          l.end.gy === link.end.gy &&
          l.start.gx === link.start.gx + 1
      );
      const rightBottom = linksArray.find(
        (l) =>
          l.start.gx === link.end.gx &&
          l.end.gx === link.end.gx + 1 &&
          l.start.gy === link.end.gy
      );

      if (rightTop && rightRight && rightBottom) {
        squaresArray.push(
          new Square(
            rightTop.start.x,
            rightTop.start.y,
            DOT_SPACING,
            DOT_SPACING,
            colours[turn]
          )
        );
        // passa pro arraysquares comunicar com o minimax
        if (turn == "p1") {
          ArraySquares.push(rightTop.start.x, rightTop.start.y, 1);
        }
        if (turn == "p2") {
          ArraySquares.push(rightTop.start.x, rightTop.start.y, 2);
        }
      }
    }
  }
}

// TRACK MOUSE

var mouse = {
  x: undefined,
  y: undefined,
};

window.addEventListener("mousemove", function (e) {
  var rect = canvas.getBoundingClientRect();

  mouse.x = e.x - rect.left;
  mouse.y = e.y - rect.top;
});

// TRACK CLICKS

var click = {
  x: undefined,
  y: undefined,
};

window.addEventListener("mousedown", function (e) {
  var rect = canvas.getBoundingClientRect();

  click.x = e.x - rect.left;
  click.y = e.y - rect.top;
});

//Inicializar o canvas
var canvas = document.querySelector("canvas");
var c = canvas.getContext("2d");
init();

function init() {
  dotCountL = document.querySelector("#gridSizeX").value; //linha
  dotCountC = document.querySelector("#gridSizeY").value; //coluna
  colours.p1 = document.querySelector("#p1Colour").value;
  colours.p2 = document.querySelector("#p2Colour").value;

  var sizeL =
    GRID_PADDING * 2 + // padding do grid
    DOT_RADIUS * 2 * dotCountL + // tamanho do ponto
    (DOT_SPACING - DOT_DIAMETER) * (dotCountL - 1); // espaço entre os pontos

  var sizeC =
    GRID_PADDING * 2 +
    DOT_RADIUS * 2 * dotCountC +
    (DOT_SPACING - DOT_DIAMETER) * (dotCountC - 1);

  canvas.width = sizeL;
  canvas.height = sizeC;

  squaresArray = [];
  linksArray = [];
  dotArray = [];

  drawDots(dotCountL, dotCountC);

  animate();
}

//'Desenha' a posição dos pontos
function drawDots(dotCountL, dotCountC) {
  for (var i = 0; i < dotCountL; i++) {
    for (var j = 0; j < dotCountC; j++) {
      dotArray.push(
        new Dot(
          i * DOT_SPACING + (GRID_PADDING + DOT_RADIUS),
          j * DOT_SPACING + (GRID_PADDING + DOT_RADIUS),
          DOT_RADIUS,
          i,
          j
        )
      );
    }
  }
}

//Atualiza Canvas
function animate() {
  requestAnimationFrame(animate);
  c.clearRect(0, 0, innerWidth, innerHeight);

  for (var i = 0; i < squaresArray.length; i++) {
    squaresArray[i].draw();
  }

  for (var i = 0; i < linksArray.length; i++) {
    linksArray[i].draw();
  }

  if (origin) {
    renderActiveLink();
  }

  for (var i = 0; i < dotArray.length; i++) {
    dotArray[i].update();
  }
}
// MUDA COR DO QUADRADO
function changeSquareColour(e, player) {
  const oldColour = colours[`p${player}`];
  const newColour = e.target.value;

  playerSquares = squaresArray.filter((square) => square.colour === oldColour);
  playerSquares.forEach((square) => (square.colour = newColour));

  colours[`p${player}`] = newColour;
}
//ATUALIZA PONTOS
function updateScores() {
  if (turn == "p2") {
    required = false;
  }
  scores[turn] = scores[turn] + 1;
  document.querySelector(`#${turn}Score`).innerHTML = scores[turn];
}

// EVENT LISTENERS
document.querySelector("#gridSizeX").addEventListener("change", function () {
  init();
});

document.querySelector("#gridSizeY").addEventListener("change", function () {
  init();
});

document.querySelector("#p1Colour").addEventListener("change", function (e) {
  changeSquareColour(e, 1);
});

document.querySelector("#p2Colour").addEventListener("change", function (e) {
  changeSquareColour(e, 2);
});

async function server() {
  //console.log("requesting");

  const a = await axios.post("http://localhost:5000", {
    dotCountL,
    dotCountC,
    tamLinks: ArrayLinks.length,
    ArrayLinks,    
    tamSquares: ArraySquares.length,
    ArraySquares,    
  });
  //console.log("response");
  console.log(a.data);

  const point = a.data;

  var origem = dotArray.find(
    (ponto) => ponto.gx == point.p1y && ponto.gy == point.p1x
  );
  var alvo = dotArray.find(
    (ponto) => ponto.gx == point.p2y && ponto.gy == point.p2x
  );
  console.log(origem, alvo);
  if (checkValidMovePC(origem, alvo) == true) {
    //console.log(origem, alvo);
    createLinkPC(origem, alvo);
  } else {
    server();
  }
}
