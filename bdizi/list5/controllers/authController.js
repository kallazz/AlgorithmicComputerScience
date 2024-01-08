import jwt from "jsonwebtoken";
import { loginUser, createUser } from "../databaseModels/User.js";
import { createEmptyUserInfo } from "../databaseModels/UserInfo.js";
import dotenv from "dotenv";
dotenv.config();

const redirectIfLoggedIn = (res) => {
    if (res.locals.user) {
        res.redirect("/");
    }
}

const handleErrors = (err) => {
    let errors = { username: "", password: "" };
    console.log(err.message);

    // Login errors
    if (err.message === "invalid username") {
        errors.username = "This username is incorrect";
    }
    if (err.message === "invalid password") {
        errors.password = "This password is incorrect";
    }

    // Sign-up errors
    if (err.message.includes("UsernameError:")) {
        errors.username = err.message.replace("UsernameError:", "");
    }

    if (err.message.includes("PasswordError:")) {
        errors.password = err.message.replace("PasswordError:", "");
    }

    return errors;
};

const maxAge = 3 * 24 * 60 * 60;
const createToken = (id) => {
    return jwt.sign({ id }, process.env.JWT_SECRET_KEY, {
        expiresIn: maxAge
    });
};

export const signup_get = (req, res) => {
    redirectIfLoggedIn(res);
    res.render("signup");
};

export const signup_post = async (req, res) => {
    const { username, password, secondPassword } = req.body;

    try {
        const newUser = await createUser(username, password, secondPassword);
        const token = createToken(newUser.id);
        res.cookie("jwt", token, { httpOnly: true, maxAge: maxAge * 1000 });
        console.log(`New user added(id = ${newUser.id})`);
        const newUserInfo = await createEmptyUserInfo(newUser.id);
        console.log(`New user info added(id = ${newUserInfo.id})`);
        res.status(201).json({ user: newUser.id });
    }
    catch(err) {
        const errors = handleErrors(err);
        res.status(400).json({ errors });
    }
};

export const login_get = (req, res) => {
    redirectIfLoggedIn(res);
    res.render("login");
};

export const login_post = async (req, res) => {
    const { username, password } = req.body;

    try {
        const user = await loginUser(username, password);
        const token = createToken(user.id);
        res.cookie("jwt", token, { httpOnly: true, maxAge: maxAge * 1000 });
        console.log(`User logged in (id = ${user.id})`)
        res.status(200).json({ user });
    }
    catch (err) {
        const errors = handleErrors(err);
        res.status(400).json({ errors });
    }
};

export const logout_get = (req, res) => {
    res.cookie("jwt", "", { maxAge: 1 });
    res.redirect("/");
};
