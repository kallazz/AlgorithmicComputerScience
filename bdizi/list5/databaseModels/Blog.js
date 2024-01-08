import database from "../database.js";

export async function getBlogById(id) {
    const [rows] = await database.execute(
        "SELECT * FROM blogs WHERE id = ?",
        [id]
    );
    return rows[0];
};

export async function getBlogByUserId(id) {
    const [rows] = await database.execute(
        "SELECT * FROM blogs WHERE user_id = ?",
        [id]
    );
    return rows[0];
};

export async function getAllBlogsDesc() {
    const [rows] = await database.execute(
        "SELECT * FROM blogs ORDER BY id DESC"
    );
    return rows;
};

export async function createBlog(userId, title, body) {
    let [result] = await database.execute(
        `
        INSERT INTO
        blogs (user_id, title, body)
        VALUES (?, ?, ?)
        `,
        [userId, title, body]
    );

    const id = result.insertId;
    const newBlog = getBlogById(id);
    return newBlog;
};

export async function deleteBlog(id) {
    console.log("delete time")
    await database.execute(
        "DELETE FROM blogs WHERE id = ?",
        [id]
    );
};
