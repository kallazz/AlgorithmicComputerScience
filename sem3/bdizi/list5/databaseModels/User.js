import bcrypt from "bcrypt";
import database from "../database.js";

export async function getUserById(id) {
    const [rows] = await database.execute(
        "SELECT * FROM users WHERE id = ?",
        [id]
    );
    return rows[0];
};

export async function loginUser(username, password) {
    const [rows] = await database.execute(
        "SELECT * FROM users WHERE username = ?",
        [username]
    ); 
    const user = rows[0];

    if (!user) {
        throw Error("invalid username");
    }
    const isPassCorrect = await bcrypt.compare(password, user.password);
    if (!isPassCorrect) {
        throw Error("invalid password");
    }

    return user;
};

export async function createUser(username, password, secondPassword) {
    const [queryResult] = await database.execute(
        "SELECT * FROM users WHERE username = ?",
        [username]
    ); 
    const existingUser = queryResult[0];

    if (existingUser) {
        throw Error("UsernameError: User with this username already exists");
    }
    else if (username.length < 6 || username.length > 30) {
        throw Error("UsernameError: Username needs to contain 6-30 characters");
    }

    if (password.length < 8) {
        throw Error("PasswordError: Password needs to contain at least 8 characters");
    }
    else if (password !== secondPassword) {
        throw Error("PasswordError: Passwords don't match");
    }

    // hash the password
    const salt = await bcrypt.genSalt();
    password = await bcrypt.hash(password, salt);

    let [result] = await database.execute(
        `
        INSERT INTO
        users (username, password)
        VALUES (?, ?)
        `,
        [username, password]
    );

    const id = result.insertId;
    const newUser = getUserById(id);
    return newUser;
};
