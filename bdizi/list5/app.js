import cookieParser from "cookie-parser";
import express from "express";
import { checkUser } from "./middleware/authMiddleware.js";
import authRoutes from "./routes/authRoutes.js";
import settingsRoutes from "./routes/settingsRoutes.js";
import blogRoutes from "./routes/blogRoutes.js";

const app = express();

app.use(express.static("public"));
app.use(express.json());
app.use(express.urlencoded({ extended: true }));
app.use(cookieParser());

app.set("view engine", "ejs");


// routes
app.listen(3000, "localhost", () => {
    console.log("Server is listening for request on port 3000");
});

app.get("*", checkUser);
app.post("*", checkUser);

app.get("/", (req, res) => {
    res.redirect("/blogs");
});

app.get("/about", (req, res) => {
    res.render("about");
});

app.use(authRoutes);
app.use(blogRoutes);
app.use(settingsRoutes);

// if the page is not found, render the 404 page
app.use((req, res) => {
    res.status(404).render("404");
});

/*

import {
    getUsers,
    getUserById,
    createUser
} from "./database.js"

app.get("/users", async (req, res) => {
    const users = await getUsers();
    res.send(users);
});

app.get("/users/:id", async (req, res) => {
    const id = req.params.id;
    const user = await getUserById(id);
    if (user == undefined) {
        res.send("nope")
    }
    res.send(user);
});

app.post("/users", async (req, res) => {
    const { username, password } = req.body;
    try {
        const user = await createUser(username, password);
        res.status(201).send(user);
    }
    catch (err) {
        console.log(err.sqlMessage);
    }
});

*/