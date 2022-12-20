const express = require("express");
const cors = require("cors");
const bodyParser = require("body-parser");
const { spawn } = require("node:child_process");

const app = express();

const PORT = 5000;

app.use(cors());
app.use(express.json());

app.get("/", (req, res) => {
  res.json("welcome to our server");
});

app.post("/", (req, res) => {
  console.log("data");
  console.log(req.body);

  let pars = [];

  for (let par of Object.keys(req.body)) pars.push(req.body[par]);
  console.log(pars);

  const ls = spawn("./servercommunic.x", pars);
  console.log(ls.data);
  ls.stdout.on("data", (data) => {
    const point = `${data}`.split(" ");
    return res.json({
      p1x: point[0],
      p1y: point[1],
      p2x: point[2],
      p2y: point[3],
    });
  });
});

app.listen(PORT, () => {
  console.log(`Server is listening on port ${PORT}`);
});
